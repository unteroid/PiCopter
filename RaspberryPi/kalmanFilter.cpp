#include "kalmanFilter.h"

class_kalmanFilter::class_kalmanFilter(){
	Q_angle_ = 0.002;
	Q_bias_ = 0;
	R_angle_ = 180;
	bias_ = 0;
}

class_kalmanFilter::~class_kalmanFilter() {
}



void class_kalmanFilter::predict(double* u, double* x, float* dt) {

	//x = F * x + B * u
	*x += (*u - bias_) * *dt;

	//P = F * P * Ft + Q
	P_[0][0] += -(P_[0][1] + P_[1][0]) * *dt + Q_angle_; // Can commit P_[1][1]*dt*dt due to very small influence
	P_[0][1] += -P_[1][1] * *dt; //Q[0][1] can be ommited as diagonals are always 0
	P_[1][0] += -P_[1][1] * *dt; //Q[1][0] can be ommited as diagonals are always 0
	P_[1][1] += Q_bias_;
}

void class_kalmanFilter::update(double* z, double* x) {

	//Innovation
	//y = z - H.x
	y_ = *z - *x;

	//Innovation covariance
	//S = H.P.H' + R
	S_ = P_[0][0] + R_angle_;

	//Optimal Kalman gain
	//K = P.H'.S^-1
	K_[0] = P_[0][0] / S_;
	K_[1] = P_[1][0] / S_;

	//Updated state estimate
	//x = x + K.y
	*x += K_[0] * y_;
	bias_ += K_[1] * y_;

	//Updated estimate covariance
	//P = (I - K.H).P	
	P_[0][0] -= K_[0] * P_[0][0];
	P_[0][1] -= K_[0] * P_[0][1];
	P_[1][0] -= K_[1] * P_[0][0];
	P_[1][1] -= K_[1] * P_[0][1];
}




