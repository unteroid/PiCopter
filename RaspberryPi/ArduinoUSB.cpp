
#include "ArduinoUSB.h"

#define RX_MAX 2000
#define RX_MIN 700
#define PITCH_RANGE 60.0F
#define ROLL_RANGE 60.0F
#define PITCH_RATE_RANGE 180.0F
#define ROLL_RATE_RANGE 180.0F
#define YAW_RATE_RANGE 100.0F

using namespace std;

class_ArduinoUSB ArduinoUSB;

class_ArduinoUSB::class_ArduinoUSB() {
	strcpy(device_, "/dev/ttyACM0");
	baud_ = 57600;
//	myfile.open("usd.txt");	
}

class_ArduinoUSB::~class_ArduinoUSB() {
   close(f_);
}

void class_ArduinoUSB::connectArduino(){
	if ((f_ = serialOpen ("/dev/ttyACM0", 230400)) < 0){
		std::cout << "USB ERROR: Failed to open Serial Bus at " << errno << std::endl;
	    }
	else if (wiringPiSetup () == -1) {
		std::cout << "Wiring pi error " << std::endl;
	}
	else { std::cout << "Arduino is connected " <<std::endl;
	while (serialDataAvail(f_)) { serialFlush(f_);}
	usleep(1000000);}

}




void class_ArduinoUSB::setPWM() {

    uint8_t sentBuff[9];
	sentBuff[0] = 220; //parrity byte
	make8_(&pwmWidths.rearLeft, &sentBuff[1]);
	make8_(&pwmWidths.rearRight, &sentBuff[3]);
	make8_(&pwmWidths.frontLeft, &sentBuff[5]);
	make8_(&pwmWidths.frontRight, &sentBuff[7]);
//	sentBuff[1] = pwmWidths.rearLeft;
//	sentBuff[2] = pwmWidths.rearRight;
//	sentBuff[3] = pwmWidths.frontLeft;
//	sentBuff[4] = pwmWidths.frontRight;
	write(f_, sentBuff, 9);

}


void class_ArduinoUSB::getReceiver() {

if (serialDataAvail(f_) > 3) {
	uint8_t receivedBuff[4];
	uint8_t z = 0;
	read(f_, receivedBuff, 4);
	for (int k = 0; k > 4; k++) {
		if ( (receivedBuff[k] & 128) == 128 ) {
			z = k;
			break;
		}
	}

	if (z == 0) {
		receivedBuff[0] = receivedBuff[0] ^ 128;
		receiverData.RCThrottle = static_cast<double>(receivedBuff[0])/100;
		receiverData.RCRoll =  ((static_cast<double>(receivedBuff[1]) - 50 )/100 * 20);
		receiverData.RCPitch =  ((static_cast<double>(receivedBuff[2]) - 50)/100 * 20);
		receiverData.RCYaw = (static_cast<double>(receivedBuff[3])  - 50)/100 * 100;
//		printf("%d %d %d %d \n", receivedBuff[0], receivedBuff[1], receivedBuff[2], receivedBuff[3]);

	} else {
		read(f_, receivedBuff, z);
	}

    }


}



inline void class_ArduinoUSB::make8_(uint16_t *tosplit, uint8_t *target) {
    *target = static_cast<uint8_t> ((*tosplit >> 8) & 0xFF);
    *(target + 1) = static_cast<uint8_t> (*tosplit & 0xFF); 
}
