#include <control_allocation.h>
#include <motor_control.h>
#include <pid.h>
#include <system_configuration.h>

// Runtime variable for controlling target trajectory
RobocockMovement targetMovement;
targetMovementl.vx = 0;
targetMovementl.vy = 0;
targetMovementl.av = 0;

// Runtime variables for PID controllers
WheelsVelocityPIDResult wheels_PIDState;
wheels_PIDState.wheelA.output = 0;
wheels_PIDState.wheelA.input_error = 0;
wheels_PIDState.wheelA.last_input_error = 0;
wheels_PIDState.wheelB.output = 0;
wheels_PIDState.wheelB.input_error = 0;
wheels_PIDState.wheelB.last_input_error = 0;
wheels_PIDState.wheelC.output = 0;
wheels_PIDState.wheelC.input_error = 0;
wheels_PIDState.wheelC.last_input_error = 0;
wheels_PIDState.wheelD.output = 0;
wheels_PIDState.wheelD.input_error = 0;
wheels_PIDState.wheelD.last_input_error = 0;

// Runtime variables for motor control
WheelSpeeds targetWheelSpeeds;

// Setup
void setup() {
    // TODO: setup input on target velocity, either using manual control or serial, maybe like a callback to set the targetMovement
}

// Loop
void loop() {
    // Calculate wheel speeds
    targetWheelSpeeds = calculateWheelSpeeds(targetMovement);

    // Get current wheel speeds
    WheelSpeeds currentWheelSpeeds = getWheelSpeeds(); // TODO: implement

    // Calculate PID values - NOTE: The PWM values at this point are not yet constrained to the range of -255 to 255 and are floats. This will be done in the next step.
    wheels_PIDState = wheelsVelocityPID(Kp, Ki, Kd, targetWheelSpeeds, currentWheelSpeeds, wheels_PIDState, dt);

    // Set motor PWM values
    // setMotorsPWM(motorPWMs);
}