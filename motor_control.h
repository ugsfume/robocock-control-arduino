#include <system_configuration.h>
#include <control_allocation.h>
#include <Arduino.h>

#ifndef MOTOR_CONTROL_H
#define MOTOR_CONTROL_H

struct MotorPWMs {
    int pwm_A;
    int pwm_B;
    int pwm_C;
    int pwm_D;
};

void setIndividualMotor(int pwmVal, int rpwm, int lpwm);
void setMotorsPWM(MotorPWMs motorPWMs);

#endif

