#ifndef I2CINTERFACE_H
#define	I2CINTERFACE_H

#include <iostream>
#include <stdio.h>
#include <stdint.h>
//#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <linux/i2c-dev.h>



class class_I2CInterface
{
public:
	class_I2CInterface();
	~class_I2CInterface();
	void  readRegister(uint8_t deviceAddress, uint8_t registerAddress, uint8_t length, uint8_t* data);
	void writeRegister(uint8_t deviceAddress, uint8_t registerAddress, uint8_t length, uint8_t* data);
	void writeBit(uint8_t deviceAddress, uint8_t registerAddress, uint8_t bitNumber, uint8_t data);
	void openInterface();

private:
	void setSlaveAddress_(uint8_t address);
	char filename_[];
	int f_;
};
extern class_I2CInterface I2CInterface;

#endif	// I2CINTERFACE_H 
