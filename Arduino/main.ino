#include <TimerOne.h>
#include <TimerFour.h>
#include <TimerThree.h>

#define RC_MIN 1150  
#define RC_MAX 1850 
#define RC_MID 1500 
#define DEAD_ZONE 80

word makeword(byte H, byte L) {
  return (word(H) << 8 | word(L));
}

word rearLeft, rearRight, frontLeft, frontRight;
byte receivedBuff[10];
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
  pinMode(21, INPUT);     //set the pin to input
  digitalWrite(21, HIGH); //use the internal pullup resistor 
  pinMode(20, INPUT);     //set the pin to input
  digitalWrite(20, HIGH); //use the internal pullup resistor
  pinMode(19, INPUT);     //set the pin to input
  digitalWrite(19, HIGH); //use the internal pullup resistor
  pinMode(18, INPUT);     //set the pin to input
  digitalWrite(18, HIGH); //use the internal pullup resistor

  attachInterrupt(2, riseRoll, RISING); // attach a PinChange Interrupt to our first pin
  attachInterrupt(3, risePitch, RISING); // attach a PinChange Interrupt to our first pin
  attachInterrupt(4, riseThrottle, RISING); // attach a PinChange Interrupt to our first pin
  attachInterrupt(5, riseYaw, RISING); // attach a PinChange Interrupt to our first pin

  Timer1.initialize(2500);
  Timer4.initialize(2500);
  
  Timer1.pwm(11, 2000);
  Timer1.pwm(12, 2000);
  Timer4.pwm(7, 2000);
  Timer4.pwm(6, 2000);
}
 
void loop()
{
    
  if(i = Serial.available() > 8) {
    z = 0;
    for(int k=0; k < 9; k++) {
      if( Serial.read() == 220) {
        z = k;
        break;
      }
    }
    
    if (z != 0) 
      while(i = Serial.available() < 7);
      
      
      for(int k=1; k < 9; k++) {
       receivedBuff[k] = Serial.read();
      }
       
      rearLeft = makeword(receivedBuff[1], receivedBuff[2]);
     // if (rearLeft > 1400) rearLeft = 1400;
      rearRight = makeword(receivedBuff[3], receivedBuff[4]);
    //  if (rearRight > 1400) rearRight = 1400;
      frontLeft = makeword(receivedBuff[5], receivedBuff[6]);
     // if (frontLeft > 1400) frontLeft = 1400;
      frontRight = makeword(receivedBuff[7], receivedBuff[8]);
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

    
    if (memcmp(exsentBuff, sentBuff, 4) != 0 ) {
      for (int i = 0; i < 4; i++) {
  	Serial.write(sentBuff[i]);
      }
    }
    
    memcpy(exsentBuff, sentBuff, 4);
    //delay(100);

}

