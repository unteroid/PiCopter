#ifndef KALMAN_H
#define KALMAN_H

class class_kalmanFilter {
public:
	class_kalmanFilter();
	virtual ~class_kalmanFilter();

	void predict(double* u, double* x, float* dt);
	void update(double* z, double* x);

private:

	double bias_;
	double P_[2][2];
	double y_;
	double Q_;
	double S_;
	double K_[2];

	double Q_angle_; //should be 0
	double Q_bias_; //can be calculated as angular velocity variance
	double R_angle_; //accelerometer variance

};

#endif //KALMAN_H
