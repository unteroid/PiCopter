
#include "PID.h"
#include <iostream>
#include <math.h>
const float a = 0.98;

class_PID::class_PID() {
}

class_PID::~class_PID() {
}

void class_PID::initialize(float kp, float ki, float kd,  float uRange) 
{
	kp_ = kp;
	ki_ = ki;
	kd_ = kd;
	uRange_ = uRange;
}



void class_PID::setPID(float kp, float ki, float kd) 
{
	kp_ = kp;
	ki_ = ki;
	kd_ = kd;
}

void class_PID::getPID() 
{
	std::cout << "P,I,D gains are:" << kp_ << ", " << ki_ << ", " << kd_ << std::endl;
}


void class_PID::calculate(double* position, double* setpoint, float* dt, double*  derivativeSource) 
{
	prevError_ = error_;

	//Anti-windup algo
	if(((output >= 	uRange_) && (*setpoint >= *position)) || ((output <= -uRange_) && (*setpoint <= *position)))
		error_ = 0;
	else if(((output >= uRange_) && (*setpoint <= *position)) || ((output <= -uRange_) && (*setpoint >= *position)))
		error_ = *setpoint - *position;

	integral_ += error_ *  *dt;
	integr_ = integral_ * ki_;
	error_ = *setpoint - *position;

	if (derivativeSource != NULL)
		derivative_ = -1 * *derivativeSource; // derivative by measurement
	else 
	{
		derivativeRaw_ = (error_ - prevError_) / *dt;
		derivative_ = derivative_ * a + (1-a)*derivativeRaw_;
	}


	output = error_ * kp_ + integral_ * ki_ + derivative_ * kd_;
	if(output >= uRange_)
		output = uRange_;
	else if(output <= -uRange_)
		output = -uRange_;
}
