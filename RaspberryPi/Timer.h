
#ifndef TIMER_H
#define	TIMER_H

#include <signal.h>
#include <iostream>

class class_Timer
{
public:
    class_Timer();
    virtual ~class_Timer();
    
    float dt;
    void get_dt();
	void initialize();
private:
    timespec oldtime_;
    timespec time_;
    

};

extern class_Timer Timer;

#endif	//TIMER_H

