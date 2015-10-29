#include <TimerOne.h>
#include <TimerFour.h>
//#include <TimerThree.h>
	
#define RC_MIN 1150	
#define RC_MAX 1850 
#define RC_MID 1500 
#define DEAD_ZONE 80

word makeword(byte H, byte L) {
	return (word(H) << 8 | word(L));
}

word rearLeft, rearRight, frontLeft, frontRight;
byte receivedBuff[10];
word receivedWord;
byte sentBuff[4];
byte exsentBuff[4];
int time[4];
int i = 0;
int z = 0;
unsigned long buffTime[4];
float percentRoll, percentPitch, percentThrottle, percentYaw;


void setup()
{
	// Pin setup
	Serial.begin(230400);
	//Serial.begin(115200);
	pinMode(21, INPUT);	 //set the pin to input
	digitalWrite(21, HIGH); //use the internal pullup resistor 
	pinMode(20, INPUT);	 
	digitalWrite(20, HIGH); 
	pinMode(19, INPUT);	 
	digitalWrite(19, HIGH); 
	pinMode(18, INPUT);	
	digitalWrite(18, HIGH); 

	attachInterrupt(2, riseRoll, RISING); // attach a PinChange Interrupt to 2 pin
	attachInterrupt(3, risePitch, RISING); // attach a PinChange Interrupt to 3 pin
	attachInterrupt(4, riseThrottle, RISING); // attach a PinChange Interrupt to 4 pin
	attachInterrupt(5, riseYaw, RISING); // attach a PinChange Interrupt to 5 pin

	Timer1.initialize(2500);
	Timer4.initialize(2500);
	
	Timer1.pwm(11, 2000);
	Timer1.pwm(12, 2000);
	Timer4.pwm(7, 2000);
	Timer4.pwm(6, 2000);
}

void loop()
{
	
	if(Serial.available() >= 8) 
	{
		z = 0;

		receivedBuff[0] = Serial.read();
		for (int k = 0; k <=7; k++)
		{
			receivedBuff[k+1] = Serial.read();
			receivedWord = makeword(receivedBuff[k], receivedBuff[k+1]);
			if ((receivedWord & 32768) == 32768) 
			{
				receivedBuff[0] = receivedBuff[k];
				receivedBuff[1] = receivedBuff[k+1];
				z = k;
				break;
			}
		}

		if (z != 0) 
			while(Serial.available() <= 6);
			
		for(int k = 2; k <= 7; k++) 
		{
			receivedBuff[k] = Serial.read();
		}

		rearLeft = makeword(receivedBuff[0], receivedBuff[1]);
		 // if (rearLeft > 1400) rearLeft = 1400;
		rearRight = makeword(receivedBuff[2], receivedBuff[3]);
		//	if (rearRight > 1400) rearRight = 1400;
		frontLeft = makeword(receivedBuff[4], receivedBuff[5]);
		 // if (frontLeft > 1400) frontLeft = 1400;
		frontRight = makeword(receivedBuff[6], receivedBuff[7]);
		// if (frontRight > 1400) frontRight = 1400; 
			
		Timer4.setPwm(7, rearLeft );
		Timer4.setPwm(6, rearRight );
		Timer1.setPwm(11, frontLeft );
		Timer1.setPwm(12, frontRight );
	}

	sentBuff[0] = (byte)percentThrottle;
	sentBuff[0] = sentBuff[0] | 128; // parrity bit 1000000
	sentBuff[1] = (byte)percentRoll;
	sentBuff[2] = (byte)percentPitch;
	sentBuff[3] = (byte)percentYaw;

	
	if (memcmp(exsentBuff, sentBuff, 4) != 0 ) 
	{
		for (int i = 0; i < 4; i++) 
		{
			 Serial.write(sentBuff[i]);
		}
	}
	
	memcpy(exsentBuff, sentBuff, 4);
	//delay(100);

}

