#ifndef GY88_H
#define GY88_H

#include <iostream>
#include <stdio.h>
#include <stdint.h>
#include "I2CInterface.h"
#include "MPU6050RegMap.h"
#include "rawData.h"

class class_GY88 
{
public:
	class_GY88();
	virtual ~class_GY88();
	
	void getSensorData(struct_rawData* rawData);
	void initialize();
private:
	void checkConnection_();
	void setSampleFreq_(uint8_t value);
	void setGyroSensivity_(uint8_t config);
	void setAccelSensivity_(uint8_t config);
//	void setMagnetSensivity_(uint8_t config);
//	void setBarometerSensivity_(uint8_t config);
	void setPWRMGMT1_(uint8_t config);
	//void setPWRMGMT2_(uint8_t config);
 	void enableByPassMode_();
	uint8_t data_[30];

};

extern class_GY88 GY88;



#endif //GY88_H
