
#include "Control.h"
#include "ArduinoUSB.h"

const uint16_t MOTOR_MAX = 2000;
const uint16_t MOTOR_MIN = 700;

class_Control Control;

class_Control::class_Control() {
}

class_Control::~class_Control() {
}

void class_Control::initialize() {

    ratePitchPID.initialize(16, 10, 0, 100);
    rateRollPID.initialize(20, 0, 0, 100);
    yawPID.initialize(7, 0.01, 0, 100);
    attitudePitchPID.initialize(4, 0, 0, 50);
    attitudeRollPID.initialize(1.5, 0, 0, 50);

}


void class_Control::update() {

	ArduinoUSB.getReceiver();
	attitudeControl_();

}


void class_Control::calibrate() {
	ArduinoUSB.pwmWidths.frontLeft = 200;
	ArduinoUSB.pwmWidths.frontRight = 200;
	ArduinoUSB.pwmWidths.rearLeft = 200;
	ArduinoUSB.pwmWidths.rearRight =200;
	ArduinoUSB.setPWM();
	getchar();
	getchar();
	ArduinoUSB.pwmWidths.frontLeft = 0;
	ArduinoUSB.pwmWidths.frontRight = 0;
	ArduinoUSB.pwmWidths.rearLeft = 0;
	ArduinoUSB.pwmWidths.rearRight = 0;
	ArduinoUSB.setPWM();
	}


inline void class_Control::updatePWM_(double* pitch, double* roll, double* yaw) {
    ArduinoUSB.pwmWidths.frontLeft =  ((ArduinoUSB.receiverData.RCThrottle * (MOTOR_MAX - MOTOR_MIN)) + MOTOR_MIN)  + *roll + *pitch + *yaw;
	antiSaturation_(&ArduinoUSB.pwmWidths.frontLeft);
    ArduinoUSB.pwmWidths.frontRight = ((ArduinoUSB.receiverData.RCThrottle * (MOTOR_MAX - MOTOR_MIN)) + MOTOR_MIN)  - *roll + *pitch - *yaw;
	antiSaturation_(&ArduinoUSB.pwmWidths.frontRight);
    ArduinoUSB.pwmWidths.rearRight = ((ArduinoUSB.receiverData.RCThrottle * (MOTOR_MAX - MOTOR_MIN)) + MOTOR_MIN) - *roll - *pitch + *yaw;
	antiSaturation_(&ArduinoUSB.pwmWidths.rearRight);
    ArduinoUSB.pwmWidths.rearLeft = ((ArduinoUSB.receiverData.RCThrottle * (MOTOR_MAX - MOTOR_MIN)) + MOTOR_MIN) + *roll - *pitch - *yaw;
	antiSaturation_(&ArduinoUSB.pwmWidths.rearLeft);
	if (ArduinoUSB.receiverData.RCThrottle == 0) {
		ArduinoUSB.pwmWidths.frontLeft = 700;
		ArduinoUSB.pwmWidths.frontRight = 700;
		ArduinoUSB.pwmWidths.rearRight = 700;
		ArduinoUSB.pwmWidths.rearLeft = 700;
	}
    ArduinoUSB.setPWM();
}

inline void class_Control::antiSaturation_(uint16_t * target) {
	if (*target > MOTOR_MAX) {
		*target = MOTOR_MAX;
	} else if (*target < MOTOR_MIN) {
		*target = MOTOR_MIN;
	}
}

//8bit number is 256 max in dec.
//so we can increase accuracy by scaling to 200% not 100%
inline void class_Control::toPercents_(uint16_t * target) {
	*target = static_cast<uint16_t>((*target - MOTOR_MIN)/((MOTOR_MAX - MOTOR_MIN)/200.0));
}

void class_Control::attitudeControl_() {
    attitudePitchPID.calculate(&AHRS.angles.pitch, &ArduinoUSB.receiverData.RCPitch, &Timer.dt, &AHRS.operableData.gyr_x);
    attitudeRollPID.calculate(&AHRS.angles.roll, &ArduinoUSB.receiverData.RCRoll, &Timer.dt, &AHRS.operableData.gyr_y);
    rateControl_(&attitudePitchPID.output, &attitudeRollPID.output);

}

void class_Control::rateControl_(double* pitchrate, double* rollrate) {

	yawPID.calculate(&AHRS.operableData.gyr_z, &ArduinoUSB.receiverData.RCYaw, &Timer.dt, NULL);
    ratePitchPID.calculate(&AHRS.operableData.gyr_x, pitchrate, &Timer.dt, NULL);
    rateRollPID.calculate(&AHRS.operableData.gyr_y, rollrate, &Timer.dt, NULL);

    updatePWM_(&ratePitchPID.output, &rateRollPID.output, &yawPID.output);
}

void class_Control::setRatePID(float KP, float KI, float KD, float KPY, float KIY) {
    ratePitchPID.setPID(KP, KI, KD);
    rateRollPID.setPID(KP, KI, KD);
	float d = 0.0;
	yawPID.setPID(KPY, KIY, d);
}

void class_Control::getRatePID() {
    ratePitchPID.getPID();
}

void class_Control::setAttitudePID(float KP, float KI, float KD) {
    attitudePitchPID.setPID(KP, KI, KD);
    attitudeRollPID.setPID(KP, KI, KD);
}

void class_Control::getAttitudePID() {
    attitudePitchPID.getPID();
}

