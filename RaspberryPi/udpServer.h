#ifndef UDP_H
#define UDP_H
#include "AHRS.h"
#include "ArduinoUSB.h"
#include "Control.h"
#include "Timer.h"

void setIP(char * ip);
void getIP();
void* udpServer(void* param);


#endif// UDP_H
