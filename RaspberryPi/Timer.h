
#ifndef TIMER_H
#define	TIMER_H

#include <signal.h>
#include <iostream>

class class_Timer
{
public:
    class_Timer();
    virtual ~class_Timer();
    
    //void start();
    //void stop();
    
    float dt;
    void get_dt();
	void initialize();
    //timer_t timerId; //id  for the posix timer
    //struct sigaction signalAction; //signal action handler struct
    //bool started;
private:
    //static void sig_handler_(int signum);
    //struct itimerspec timeToSet_; //time to be set
    //struct timespec timeValue_; //timer expiration value
    //struct timespec timeInterval_; //timer period
    timespec oldtime_;
    timespec time_;
    //timespec iterationtime_;
    

};

extern class_Timer Timer;

#endif	//TIMER_H

