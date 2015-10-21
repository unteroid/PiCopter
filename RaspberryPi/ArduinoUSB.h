
#ifndef ARDUINOUSB_H
#define ARDUINOUSB_H

#include <iostream>//include system librarys
#include <fstream>
#include <stdio.h> //for printf
#include <stdint.h> //uint8_t definitions
#include <stdlib.h> //for exit(int);
#include <string.h> //for errno
#include <errno.h> //error output
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <wiringPi.h>
#include <wiringSerial.h>

using namespace std;


struct struct_pwmWidths
{
    uint16_t frontRight;
    uint16_t rearRight;
    uint16_t rearLeft;
    uint16_t frontLeft;
};

struct struct_receiverData
{
    float RCThrottle;
    double RCPitch;
    double RCRoll;
    double RCYaw;
};

class class_ArduinoUSB
{
public:
    class_ArduinoUSB();
    virtual ~class_ArduinoUSB();
    void setPWM();
    void getReceiver();
    void connectArduino();
    struct_pwmWidths pwmWidths;
    struct_receiverData receiverData;
    ofstream myfile;
private:
    char device_[];
    int f_;
    uint16_t baud_;
    void make8_(uint16_t *tosplit, uint8_t *target);

};

extern class_ArduinoUSB ArduinoUSB;

#endif  // ARDUINOUSB_H

