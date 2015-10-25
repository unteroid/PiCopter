
void riseRoll()        
{
    //timer for roll PPM is starting to count
    buffTime[0] = micros();
    //rise is captured, detatching now
    detachInterrupt(2);
    //attaching fall function
    attachInterrupt(2, fallRoll, FALLING); 
}
 
void fallRoll()        
{  
    //PPM length is calculated
    time[0] = micros() - buffTime[0];
    rcDeadZone(&time[0], &percentRoll);
    //fall is captured, detatching
    detachInterrupt(2);
    //attaching rise back
    attachInterrupt(2, riseRoll,RISING);
}
  
void risePitch()        
{
    buffTime[1] = micros();
    detachInterrupt(3);
    attachInterrupt(3, fallPitch, FALLING); 
}
 
void fallPitch()        
{
    time[1] = micros() - buffTime[1];
    rcDeadZone(&time[1], &percentPitch);
    detachInterrupt(3);
    attachInterrupt(3, risePitch,RISING);
}

void riseThrottle()        
{
    buffTime[2] = micros();
    detachInterrupt(4);
    attachInterrupt(4, fallThrottle, FALLING); 
}
 
void fallThrottle()       
{
    time[2] = micros() - buffTime[2];
    percentThrottle = (double)(time[2] - RC_MIN)/(RC_MAX - RC_MIN)*100;
    if (percentThrottle < 0) {
      percentThrottle = 0; 
    }else if (percentThrottle > 100 ){
      percentThrottle = 100;};
    detachInterrupt(4);
    attachInterrupt(4, riseThrottle,RISING);
} 
void riseYaw()      
{
    buffTime[3] = micros();
    detachInterrupt(5);
    attachInterrupt(5, fallYaw, FALLING); 
}
 
void fallYaw()        
{
    time[3] = micros() - buffTime[3];
    rcDeadZone(&time[3], &percentYaw);
    detachInterrupt(5);
    attachInterrupt(5, riseYaw,RISING);
}

