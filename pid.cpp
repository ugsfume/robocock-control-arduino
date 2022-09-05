#include <pid.h>

// Velocity PID controller
VelocityPIDResult velocityPID(float Kp, float Ki, float Kd, float target_input, float current_input, VelocityPIDResult last_result, float dt) {
    // Based on: CVn = CVn-1 + Kp * (error - errorn-1) + Ki * error * dt + Kd * (error - 2 * errorn-1 + errorn-2) / dt
    // Calculate error
    float input_error = target_input - current_input;
    // Caculate P term
    float P = Kp * (input_error - last_result.input_error);
    // Calculate I term
    float I = Ki * input_error * dt;
    // Calculate D term
    float D = Kd * (input_error - 2 * last_result.input_error + last_result.last_input_error) / dt;
    // Calculate output
    float output = last_result.output + P + I + D;
    // Return result
    VelocityPIDResult result;
    result.output = output;
    result.input_error = input_error;
    result.last_input_error = last_result.input_error;
}

WheelsVelocityPIDResult wheelsVelocityPID(float Kp, float Ki, float Kd, WheelSpeeds target_input, WheelSpeeds current_input, WheelsVelocityPIDResult last_result, float dt) {
    WheelsVelocityPIDResult result;
    result.wheelA = velocityPID(Kp, Ki, Kd, target_input.av_A, current_input.av_A, last_result.wheelA, dt);
    result.wheelB = velocityPID(Kp, Ki, Kd, target_input.av_B, current_input.av_B, last_result.wheelB, dt);
    result.wheelC = velocityPID(Kp, Ki, Kd, target_input.av_C, current_input.av_C, last_result.wheelC, dt);
    result.wheelD = velocityPID(Kp, Ki, Kd, target_input.av_D, current_input.av_D, last_result.wheelD, dt);
    return result;
}

