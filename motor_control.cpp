#include <motor_control.h>

void setIndividualMotor(int pwmVal, int rpwm, int lpwm){
    // Bound the pwmVal between -255 and 255 (Which should not be exceeded anyway!)
    if (pwmVal > 255) {
        pwmVal = 255;
    } else if (pwmVal < -255) {
        pwmVal = -255;
    }
    if (pwmVal > 0) {
        analogWrite(rpwm, pwmVal);
        analogWrite(lpwm, 0);
    } else if (pwmVal < 0) {
        analogWrite(rpwm, 0);
        analogWrite(lpwm, -pwmVal);
    } else {
        analogWrite(rpwm, 0);
        analogWrite(lpwm, 0);
    }
}

void setMotorsPWM(MotorPWMs motorPWMs) {
    setIndividualMotor(motorPWMs.pwm_A, MOTOR_A_RPWM, MOTOR_A_LPWM);
    setIndividualMotor(motorPWMs.pwm_B, MOTOR_B_RPWM, MOTOR_B_LPWM);
    setIndividualMotor(motorPWMs.pwm_C, MOTOR_C_RPWM, MOTOR_C_LPWM);
    setIndividualMotor(motorPWMs.pwm_D, MOTOR_D_RPWM, MOTOR_D_LPWM);
}