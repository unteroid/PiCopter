#ifndef OPERABLEDATA_H
#define OPERABLEDATA_H


#include <time.h>
#include <cstdint>
#include <unistd.h>

struct struct_operableData {

	double gyr_x;
	double gyr_x_f;
	double gyr_x_ang;
	double gyr_y;
	double gyr_y_f;
	double gyr_y_ang;
	double gyr_z;
	double acc_p;
	double acc_q;
	double acc_p_f;
	double acc_q_f;
	double acc_r;
	double acc_x;
	double acc_y;
	double acc_z;
	double temperature;
	double mag_x;
	double mag_y;
	double mag_z;
	double pressure;
	double dt;
};


#endif //OPERABLEDATA_H
