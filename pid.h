#include <control_allocation.h>

#ifndef PID_H
#define PID_H
struct VelocityPIDResult {
    float output; // The duty cycle of the motor (-255 to 255)
    float input_error; // The difference between the target omega and the current omega
    float last_input_error; // The error from the previous iteration
};

struct WheelsVelocityPIDResult {
    VelocityPIDResult wheelA;
    VelocityPIDResult wheelB;
    VelocityPIDResult wheelC;
    VelocityPIDResult wheelD;
};

VelocityPIDResult velocityPID(float Kp, float Ki, float Kd, float target_input, float current_input, VelocityPIDResult last_result, float dt);

WheelsVelocityPIDResult wheelsVelocityPID(float Kp, float Ki, float Kd, WheelSpeeds target_input, WheelSpeeds current_input, WheelsVelocityPIDResult last_result, float dt);
#endif