#include "GY88.h"

class_GY88 GY88;

class_GY88::class_GY88 () {
}

class_GY88::~class_GY88() {
}

void class_GY88::getSensorData(struct_rawData* rawData) 
{
	I2CInterface.readRegister(MPU6050_ADDRESS, MPU6050_RA_ACCEL_XOUT_H, 14, data_);
	rawData->acc_x = static_cast<int16_t>((data_[0]<<8)|data_[1]);
	rawData->acc_y = static_cast<int16_t>((data_[2]<<8)|data_[3]);
	rawData->acc_z = static_cast<int16_t>((data_[4]<<8)|data_[5]);
	rawData->temperature = static_cast<int16_t>((data_[6]<<8)|data_[7]);
	rawData->gyr_x = static_cast<int16_t>((data_[8]<<8)|data_[9]);
	rawData->gyr_y = static_cast<int16_t>((data_[10]<<8)|data_[11]);
	rawData->gyr_z = static_cast<int16_t>((data_[12]<<8)|data_[13]); 
	
}

void class_GY88::checkConnection_() 
{
	I2CInterface.readRegister(MPU6050_ADDRESS, MPU6050_RA_WHO_AM_I, 1, data_);
	if((uint8_t)data_[0] == 0x68) {
		std::cout << "GY88 is connected" << std::endl;
	} else {
		std::cout << "GY88 ERROR: GY88 connection failed" << std::endl;
	}
}

void class_GY88::initialize() 
{
	uint8_t buf[25];
	checkConnection_();
	setPWRMGMT1_(MPU6050_CLOCK_PLL_XGYRO);
	setSampleFreq_(0);
	setGyroSensitivity_(MPU6050_GYRO_FS_500);
	setAccelSensitivity_(MPU6050_ACCEL_FS_8);
	enableByPassMode_();
}

void class_GY88::setSampleFreq_(uint8_t value) {
	I2CInterface.writeRegister(MPU6050_ADDRESS, MPU6050_RA_SMPLRT_DIV, 1, &value);
}

void class_GY88::setGyroSensitivity_(uint8_t config) {
	I2CInterface.writeRegister(MPU6050_ADDRESS, MPU6050_RA_GYRO_CONFIG, 1, &config);
}

void class_GY88::setAccelSensitivity_(uint8_t config) {
	I2CInterface.writeRegister(MPU6050_ADDRESS, MPU6050_RA_ACCEL_CONFIG, 1, &config);
}

void class_GY88::setPWRMGMT1_(uint8_t config) {
	I2CInterface.writeBit(MPU6050_ADDRESS, MPU6050_RA_PWR_MGMT_1, 6, false);
	I2CInterface.writeRegister(MPU6050_ADDRESS, MPU6050_RA_PWR_MGMT_1, 1, &config);
}

void class_GY88::enableByPassMode_() {
	uint8_t data = 0b00000010;
	I2CInterface.writeRegister(MPU6050_ADDRESS, MPU6050_RA_INT_PIN_CFG, 1, &data);
}
