#ifndef AHRSCLASS_H
#define AHRSCLASS_H

#include <iostream>
#include <time.h>
#include <cstdint>
#include <unistd.h>
#include <math.h>
#include "I2CInterface.h"
#include "Timer.h"
#include "MPU6050RegMap.h"
#include "GY88.h"
#include "rawData.h"
#include "calibData.h"
#include "Angles.h"
#include "operableData.h"
#include "kalmanFilter.h"

class class_AHRS 
{
public:
	class_AHRS();
	virtual ~class_AHRS();
	void update();
	void calibrateAngle();
	void getAngleError();
	double roll_error, pitch_error;

	struct_angles angles;
	struct_calibData calibdata;
	struct_operableData operableData;
private:

	struct_rawData rawData_;
	void getRawData_();
	void convertRawToOperable_();
	void filterData_();
	void fuseData_();
	class_kalmanFilter kalmanFilter;
};
	extern class_AHRS AHRS;

#endif //AHRSCLASS_H
