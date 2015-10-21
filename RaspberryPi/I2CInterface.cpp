#include "I2CInterface.h"

class_I2CInterface I2CInterface;

class_I2CInterface::class_I2CInterface()
{
    strcpy(filename_, "/dev/i2c-1");
    openInterface();
}

class_I2CInterface::~class_I2CInterface()
{
    close(f_);
}

void class_I2CInterface::openInterface()
{
    if ((f_ = open(filename_, O_RDWR)) < 0)
    {
        std::cout << "I2C ERROR: Failed to open I2C bus. Check your file path. Or maybe you've forgot sudo?" << std::endl;
    }
}

void  class_I2CInterface::readRegister(uint8_t deviceAddress, uint8_t registerAddress, uint8_t length, uint8_t* data)
{
    setSlaveAddress_(deviceAddress);
    if (i2c_smbus_read_i2c_block_data(f_, registerAddress, length, data) != length)
    {
        std::cout << "I2C ERROR: Incorrect number of bytes read" << std::endl;
    }
}

void  class_I2CInterface::writeRegister(uint8_t deviceAddress, uint8_t registerAddress, uint8_t length, uint8_t* data)
{
    setSlaveAddress_(deviceAddress);
    if (i2c_smbus_write_i2c_block_data(f_, registerAddress, length, data) < 0)
    {
        std::cout << "I2C ERROR: I2C write failed writing to register" << std::hex << registerAddress << std::endl;
    };
}

void class_I2CInterface::writeBit(uint8_t deviceAddress, uint8_t registerAddress, uint8_t bitNumber, uint8_t data) {
    uint8_t b;
    readRegister(deviceAddress, registerAddress, 1, &b);
    b = (data != 0) ? (b | (1 << bitNumber)) : (b & ~(1 << bitNumber));
    writeRegister(deviceAddress, registerAddress, 1, &b);
}

void  class_I2CInterface::setSlaveAddress_(uint8_t address)
{
    if (ioctl(f_, I2C_SLAVE, address) < 0)
    {
        std::cout << "I2C ERROR: Failed to set I2C slave address. Error occured while opening file descriptor. " << " errno " << errno << std::endl;
    }
}

