#include <iostream>//include system librarys
#include <unistd.h>
#include "ArduinoUSB.h"

 uint16_t rearLeft;
 uint16_t rearRight;
 uint16_t frontLeft;
 uint16_t frontRight;
 uint8_t widthsChar[8]; 
void make8(uint16_t *tosplit, uint8_t *target);


int main() {
	rearLeft = 800;
	frontRight = 800;
	rearRight = 700;
	frontLeft = 700;

	ArduinoUSB.connectArduino();
	usleep(1000000);
	
   for (;;) {
	
	scanf(" %d, %d, %d, %d", &rearLeft, &rearRight, &frontLeft, &frontRight);
    ArduinoUSB.setPWM(&rearLeft, &rearRight, &frontLeft, &frontRight); 
}
}

void make8(uint16_t *tosplit, uint8_t *target) {
    *target = static_cast<uint8_t> ((*tosplit >> 8) & 0xFF);
    *(target + 1) = static_cast<uint8_t> (*tosplit & 0xFF); 
}
