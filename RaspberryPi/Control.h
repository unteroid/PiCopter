
#ifndef CONTROL_H
#define	CONTROL_H

#include "PID.h"
#include "AHRS.h"
#include "Timer.h"


class class_Control
{
public:
	class_Control();
	virtual ~class_Control();

	void initialize();
	void update();
	void setRatePID(float kp, float ki, float kd, float kpy, float kiy);
	void getRatePID();
	void setAttitudePID(float kp, float ki, float kd);
	void getAttitudePID();
	class_PID ratePitchPID, rateRollPID, rateYawPID;
	class_PID attitudePitchPID, attitudeRollPID;
	class_PID yawPID;
	FILE *f;

private:
	void updatePWM_( double* pitch, double* roll, double* yaw);
	void saturation_( uint16_t * target);
//	void toPercents_(uint16_t * target);
	void rateControl_(double* pitchrate, double* rollrate);
	void attitudeControl_();
};

extern class_Control Control;

#endif	// CONTROL_H 

