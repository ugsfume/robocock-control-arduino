#include <system_configuration.h>

#ifndef CONTROL_ALLOCATION_H
#define CONTROL_ALLOCATION_H
// Define data types for Robocock movement
// All linear movement is in m/s and angular movement is in rad/s

struct RobocockMovement {
    float vx; // velocity in x direction
    float vy; // velocity in y direction
    float av; // angular velocity (clockwise is positive)
};

struct WheelSpeeds {
    float av_A; // angular velocity of wheel A
    float av_B; // angular velocity of wheel B
    float av_C; // angular velocity of wheel C
    float av_D; // angular velocity of wheel D
};

// Constants
const float sqrt2 = 1.41421356237; // square root of 2

WheelSpeeds calculateWheelSpeeds(RobocockMovement m);
#endif