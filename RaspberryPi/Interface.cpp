#include <stdio.h>
#include <iostream>
#include "Interface.h"

using namespace std;

void* interfaceFunc(void* param) {

	//cout << "enter menu for info" << endl;
	//cin >> command;
	//if (command == "7") {

	int command;

	cout << endl <<  "\
		1: Set rate PID \n \
		2: Set attitude PID \n \
		3: Get rate PID \n \
		4: Get attitude PID \n \
		5: Set sensor error \n \
		6: Get current sensor error \n \
		7: Get current UDP client's IP \n \
		8: Set current UDP client's IP \n \
		9: Menu list \n" << endl;

	for(;;) {
	command = 0;
	cin >> command;
	if (command == 1) {
		double d, k, i, ky, iy;
		cout << "set rate P" << endl;
		cin >> k;
		cout << "set rate I" << endl;
		cin >> i;
		cout << "set rate D" << endl;
		cin >> d;
		cout << "set yaw P" << endl;
		cin >> ky;
		cout << "set yaw I" << endl;
		cin >> iy;
	//	ky = 0.0;
	//	iy = 0.0;
		Control.setRatePID(k, i, d, ky, iy);
		Control.rateRollPID.integral_ = 0;
		Control.ratePitchPID.integral_ = 0;
		Control.yawPID.integral_ = 0;
		Control.getRatePID();
		continue;
	} else if (command == 2) {
		double k, i, d;
		cout << "set attitude P" << endl;
		cin >> k;
		cout << "set attitude I" << endl;
		cin >> i;
		cout << "set attitude D" << endl;
		cin >> d;
		Control.setAttitudePID(k, i, d);
		Control.attitudeRollPID.integral_ = 0;
		Control.attitudePitchPID.integral_ = 0;

		Control.getAttitudePID();
		continue;
	} else if (command == 3) {
		cout << "rate PID:" << endl;
		Control.getRatePID();
		continue;
	} else if (command == 4) {
		cout << "attitude PID:" << endl;
		Control.getAttitudePID();
		continue;
	} else if (command == 5) {
		cout << "set roll error" << endl;
		cin  >> AHRS.roll_error;
		cout << "set pitch error" << endl;
		cin >> AHRS.pitch_error;
		//AHRS.calibrateAngle(roll_error, pitch_error);
		continue;
	} else if (command == 6) {
		AHRS.getAngleError();
		continue;
	 }else if (command == 7) {
		cout << "Current UDP clent's IP is: ";
 		getIP();
	} else if (command == 8) {
		cout << "Enter UDP client's IP xx.xx.xx.xx" << endl;
		char ip[30];
		scanf("%s", &ip);
		setIP(ip);
		cout  << "IP is changed" << endl;
		continue;
	} else if (command == 9) {
		cout << endl <<  "\
			1: Set rate PID \n \
			2: Set attitude PID \n \
			3: Get rate PID \n \
			4: Get attitude PID \n \
			5: Set sensor error \n \
			6: Get current sensor error \n \
			7: Get current UDP client's IP \n \
			8: Set current UDP client's IP \n \
			9: Menu list \n" << endl;
		continue;
	};
	};

}
