#include "AHRS.h"


class_AHRS AHRS;
const double pi = 3.141592653589793;
const float a = 0.8;

class_AHRS::class_AHRS() {
}

class_AHRS::~class_AHRS(){ 
}


void class_AHRS::update() {
	getRawData_();
	convertRawToOperable_();
	filterData_();
	fuseData_();
	calibrateAngle();
}

void class_AHRS::getRawData_() {
	GY88.getSensorData(&rawData_);
}


void class_AHRS::convertRawToOperable_() {
	operableData.gyr_x = rawData_.gyr_x/65.5;
	operableData.gyr_y = rawData_.gyr_y/65.5;
	operableData.gyr_z = rawData_.gyr_z/65.5;
	operableData.acc_x = double(rawData_.acc_x)/4096;
	operableData.acc_y = double(rawData_.acc_y)/4096;
	operableData.acc_z = double(rawData_.acc_z)/4096;
//	operableData.gyr_x_ang = operableData.gyr_x_ang + operableData.gyr_x*Timer.dt;
//	operableData.gyr_y_ang = operableData.gyr_y_ang + operableData.gyr_y*Timer.dt;
	operableData.acc_q = 180/pi * atan(rawData_.acc_y / sqrt( pow(rawData_.acc_x, 2) + pow(rawData_.acc_z, 2) )); //  radian to degrees * atan... x axis
	operableData.acc_p = -1*(180/pi * atan(rawData_.acc_x / sqrt( pow(rawData_.acc_y, 2) + pow(rawData_.acc_z, 2) ))); // -1 * radian to degrees * atan... y axis
}

void class_AHRS::filterData_() {
	//exponential decay low-pass filter
	operableData.acc_q_f = (operableData.acc_q_f)* a + (1-a)*operableData.acc_q;
	operableData.acc_q_f = (operableData.acc_q_f)* a + (1-a)*operableData.acc_q;
	operableData.gyr_x_f = (operableData.gyr_x_f)* 0.99 + (1-0.99)*operableData.gyr_x;
	operableData.gyr_y_f = (operableData.gyr_y_f)* 0.99 + (1-0.99)*operableData.gyr_y;
}

void class_AHRS::fuseData_() {
	//complementary filter
	//angles.roll =  (operableData.gyr_y_ang + operableData.gyr_y*Timer.dt)*a + (1-a)*operableData.acc_p;
	//angles.pitch  =  (operableData.gyr_x_ang + operableData.gyr_x*Timer.dt)*a + (1-a)*operableData.acc_q;
	kalmanFilter.predict(&angles.roll_off, &operableData.gyr_y, &Timer.dt);
	kalmanFilter.update(&operableData.acc_p, &angles.roll_off);
	kalmanFilter.predict(&angles.pitch_off, &operableData.gyr_x, &Timer.dt);
	kalmanFilter.update(&operableData.acc_q, &angles.pitch_off);

}

void class_AHRS::calibrateAngle() {
	angles.roll = angles.roll_off - roll_error;
	angles.pitch = angles.pitch_off - pitch_error;
	//fprintf(stderr, "%1f  %1f \n", roll_error, pitch_error);
}
void class_AHRS::getAngleError() {
	fprintf(stderr, "%1f %1f \n", roll_error, pitch_error);
}
