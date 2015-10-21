
#ifndef PID_H
#define	PID_H


class class_PID
{
public:
    class_PID();
    virtual ~class_PID();
    void initialize(float kp, float ki, float kd, float uRange);
    void calculate(double* position, double* setpoint, float* dt, double* derivativeSource);
    void setPID(float kPr, float kIn, float kDif);
    void getPID();
    double output;
    float proportional_, integral_, derivative_, derivativeRaw_;

	double integr_;
	float err;
private:
    float kp_, ki_, kd_;
    double derivativeSource_, oldDerivativeSource_;
    float iLim_;
    float uRange_;
    float prevError_;
    float error_;

};

#endif	// PID_H 

