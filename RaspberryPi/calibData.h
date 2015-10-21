#ifndef CALIBDATA_H
#define CALIBDATA_H


#include <time.h>
#include <cstdint>
#include <unistd.h>

struct struct_calibData {

	double gyr_x;
	double gyr_y;
	double gyr_z;
	double acc_p;
	double acc_q;
	double acc_r;
	double temperature;
	double mag_x;
	double mag_y;
	double mag_z;
	double pressure;
	double dt;
};


#endif //CALIBDATA_H
