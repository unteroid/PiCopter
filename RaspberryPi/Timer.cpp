#include "Timer.h"

#define PERIOD 2500000

class_Timer Timer;
//	FILE * myfile;

class_Timer::class_Timer()
{
	oldtime_.tv_sec = 0;
	oldtime_.tv_nsec = 0;
	time_.tv_sec = 0;
	time_.tv_nsec = 0;
    //timer_create(CLOCK_REALTIME, NULL, &timerId);
 }

class_Timer::~class_Timer()
{
}

void class_Timer::initialize() {
    clock_gettime(CLOCK_MONOTONIC, &time_);
//	myfile = fopen("freq.txt","w");

}


void class_Timer::get_dt()
{
    oldtime_ = time_;
    clock_gettime(CLOCK_MONOTONIC, &time_);
    dt = ((static_cast<int64_t>(time_.tv_sec) * 1000000000 + static_cast<int64_t>(time_.tv_nsec)) - (static_cast<int64_t>(oldtime_.tv_sec) * 1000000000 + static_cast<int64_t>(oldtime_.tv_nsec))) / 1000000000.0;
	if (dt < 0.0025) {
	uint16_t delay = static_cast<uint16_t>(2400.0 - dt*1000000.0);
		usleep(delay);
		clock_gettime(CLOCK_MONOTONIC, &time_);
    dt = ((static_cast<int64_t>(time_.tv_sec) * 1000000000 + static_cast<int64_t>(time_.tv_nsec)) - (static_cast<int64_t>(oldtime_.tv_sec) * 1000000000 + static_cast<int64_t>(oldtime_.tv_nsec))) / 1000000000.0;
	}
//			fprintf(myfile, "dt is %fhz \n",1/dt);

//	if 

}
