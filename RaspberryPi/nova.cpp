#include <pthread.h>
#include <sched.h>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <termios.h>
#include "udpServer.h"
#include "AHRS.h"
#include "Timer.h"
#include "GY88.h"
#include "Control.h"
#include "ArduinoUSB.h"
#include "Interface.h"
#include <pthread.h>
#include <sched.h>

using namespace std;



void* logger(void* file) 
{
	for(;;) 
	{
		fprintf((FILE*)file,"xypq: %1f %1f %1f %1f \n", ArduinoUSB.receiverData.RCRoll, ArduinoUSB.receiverData.RCPitch, AHRS.angles.roll, AHRS.angles.pitch);
		usleep(2500);
	}
}

int main() {

	//setting thread priority to realtime fifo
	pthread_t mainThread = pthread_self();
	struct sched_param params;
	params.sched_priority = sched_get_priority_max(SCHED_FIFO);
	pthread_setschedparam(mainThread,SCHED_FIFO, &params);
	int policy = 0;
	int ret = pthread_getschedparam(mainThread, &policy, &params);
	if  (ret != 0) 
		fprintf(stderr, "SHED ERROR: sched is set wrong\n");

	FILE *f;
	f = fopen("output.txt", "w");
	//initialize stuff
	GY88.initialize();
	Control.initialize();
	ArduinoUSB.connectArduino();
	Timer.initialize();

	//set PIDs
	float k, i, d, ky, iy, dy;
	scanf(" %f, %f, %f, %f, %f", &k, &i, &d, &ky, &iy);
	Control.setRatePID(k, i, d, ky, iy);
	scanf(" %f, %f, %f", &k, &i, &d);
	Control.setAttitudePID(k, i, d);

	float dtSum = 0;
	//waiting for 5 seconds for filter values to stabilize
	fprintf(stderr, "wait for a moment for filter to stabilize \n");
	while ( dtSum < 5 ) 
	{
		AHRS.update();
		Timer.get_dt();
		dtSum = Timer.dt + dtSum;
	}

	pthread_t thread_logger;
//	ret = pthread_create(&thread_logger, NULL, logger, (void *)f);
//	if (ret != 0) fprintf(stderr, "THREAD ERROR: can't create logger thread");


	pthread_t thread_udpServer;
	ret = pthread_create(&thread_udpServer, NULL, udpServer, NULL);
	if (ret != 0) fprintf(stderr, "THREAD ERROR: can't create udp thread");


	pthread_t thread_interface;
	ret = pthread_create(&thread_interface, NULL, interfaceFunc, NULL);
	if (ret != 0) fprintf(stderr, "THREAD ERROR: can't create interface thread");



	for(;;) {
		AHRS.update();
		Control.update();
		Timer.get_dt();
	}


	return 0;
}
