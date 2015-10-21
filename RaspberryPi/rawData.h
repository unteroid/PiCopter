#ifndef RAWDATA_H
#define RAWDATA_H


#include <time.h>
#include <cstdint>
#include <unistd.h>

struct struct_rawData {

	int16_t gyr_x;
	int16_t gyr_y;
	int16_t gyr_z;
	int16_t acc_x;
	int16_t acc_y;
	int16_t acc_z;
	int16_t temperature;
	int16_t mag_x;
	int16_t mag_y;
	int16_t mag_z;
	int16_t pressure;
};


#endif //RAWDATA_H
