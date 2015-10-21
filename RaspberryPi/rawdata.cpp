#include <iostream>
#include "I2CInterface.h"
#include "MPU6050RegMap.h"
#include <time.h>
#include <cstdint>
#include <unistd.h>


int main(){
	uint8_t data[14];	
	int16_t accX, accY, accZ, gyrX, gyrY, gyrZ, temp;
	float gyrXA, gyrYA, gyrZA;
	float dt;
	timespec curTime, oldTime;
	clock_gettime(CLOCK_REALTIME, &curTime);
	
	uint8_t pwrmgmt = 0x01;
	I2CInterface.writeRegister(MPU6050_ADDRESS, MPU6050_RA_PWR_MGMT_1, 1, &pwrmgmt);
	usleep(10000);
	
	gyrXA = 0;
	gyrYA = 0; 
	gyrZA = 0;
	FILE * f;
	f = fopen("data.txt", "w");
	
	//fprintf(f, "accX accY accZ gyrX gyrY gyrZ gyrXA gyrYA gyrZA dt \n");
	for (;;) {

	I2CInterface.readRegister(MPU6050_ADDRESS, MPU6050_RA_ACCEL_XOUT_H, 14, data);
	accX = static_cast<int16_t>((data[0]<<8)|data[1]);
	accY = static_cast<int16_t>((data[2]<<8)|data[3]);
	accZ = static_cast<int16_t>((data[4]<<8)|data[5]);
	temp = static_cast<int16_t>((data[6]<<8)|data[7]);
	gyrX = static_cast<int16_t>((data[8]<<8)|data[9]);
	gyrY = static_cast<int16_t>((data[10]<<8)|data[11]);
	gyrZ = static_cast<int16_t>((data[12]<<8)|data[13]);
	oldTime = curTime;
	clock_gettime(CLOCK_REALTIME, &curTime);
	dt = ( (static_cast<int64_t>(curTime.tv_sec)*1000000000 + static_cast<int64_t>(curTime.tv_nsec)) - (static_cast<int64_t>(oldTime.tv_sec)*1000000000 + 
 	static_cast<int64_t>(oldTime.tv_nsec)) ) /1000000000.0;
	//gyrXA = gyrXA+gyrX*dt;
	//gyrYA = gyrYA+gyrY*dt;
	//gyrZA = gyrZA+gyrZ*dt;

	//fprintf(f, "%7d %7d %7d %7d %7d %7d %.5f %.5f %.5f %.5f \n", accX, accY, accZ, gyrX, gyrY, gyrZ, gyrXA, gyrYA, gyrZA, dt);
	printf( "%7d %7d %7d %7d %7d %7d  \n", accX, accY, accZ, gyrX, gyrY, gyrZ);
	}

	return 0;
}



