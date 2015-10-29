 
#include "ArduinoUSB.h"

#define RX_MAX 2000
#define RX_MIN 700
#define PITCH_RANGE 20.0F
#define ROLL_RANGE 20.0F
#define YAW_RATE_RANGE 100.0F

using namespace std;

class_ArduinoUSB ArduinoUSB;

class_ArduinoUSB::class_ArduinoUSB() 
{
	strcpy(device_, "/dev/ttyACM0");
	baud_ = 230400;
}

class_ArduinoUSB::~class_ArduinoUSB() 
{
   close(f_);
}

void class_ArduinoUSB::connectArduino()
{
	if ((f_ = serialOpen (device_, baud_)) < 0)
	{
		std::cout << "USB ERROR: Failed to open Serial Bus at " << errno << std::endl;
	}
	else if (wiringPiSetup () == -1) 
	{
		std::cout << "Wiring pi error " << std::endl;
	}
	else 
	{ 
		std::cout << "Arduino is connected " <<std::endl;
		while (serialDataAvail(f_)) 
		{ 
			serialFlush(f_);
		}
		usleep(1000000);
	}

}





void class_ArduinoUSB::setPWM() 
{

    uint8_t sentBuff[8];
    *pwmWidths.rearLeft = *pwmWidths.rearLeft | 32768 //parrity bit 1000 0000 0000 0000
	make8_(&pwmWidths.rearLeft, &sentBuff[0]);
	make8_(&pwmWidths.rearRight, &sentBuff[2]);
	make8_(&pwmWidths.frontLeft, &sentBuff[4]);
	make8_(&pwmWidths.frontRight, &sentBuff[6]);
	write(f_, sentBuff, 8);
}


void class_ArduinoUSB::getReceiver()
 {

	if (serialDataAvail(f_) > 3) 
	{
		uint8_t receivedBuff[4];
		uint8_t z = 0;
		read(f_, receivedBuff, 4);
		for (int k = 0; k > 4; k++) 
		{
			if ( (receivedBuff[k] & 128) == 128 ) 
			{
				z = k;
				break;
			}
		}

		if (z == 0) 
		{
			receivedBuff[0] = receivedBuff[0] ^ 128;
			receiverData.RCThrottle = static_cast<double>(receivedBuff[0])/100;
			receiverData.RCRoll =  ((static_cast<double>(receivedBuff[1]) - 50 )/100 * ROLL_RANGE );
			receiverData.RCPitch =  ((static_cast<double>(receivedBuff[2]) - 50)/100 * PITCH_RANGE );
			receiverData.RCYaw = (static_cast<double>(receivedBuff[3])  - 50)/100 * YAW_RATE_RANGE;
		} 
		else 
		{
			read(f_, receivedBuff, z);
		}

	}
}



inline void class_ArduinoUSB::make8_(uint16_t *tosplit, uint8_t *target) 
{
    *target = static_cast<uint8_t> ((*tosplit >> 8) & 0xFF);
    *(target + 1) = static_cast<uint8_t> (*tosplit & 0xFF); 
}
