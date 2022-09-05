#ifndef SYSTEM_CONFIGURATION_H
#define SYSTEM_CONFIGURATION_H

// Define wheel parameters
const float RW = 0.05; // radius of the wheels in meters
const float RO = 0.1; // distance between the center of the robot and the center of the wheels in meters

// Define motor / encoder parameters
const float CPR = 1000; // counts per revolution (just a placeholder for now)

// Define PID parameters
const float Kp = 0.1; // proportional gain
const float Ki = 0.1; // integral gain
const float Kd = 0.1; // derivative gain

// Motor output pins
// Wheel A
#define RPWM_1 4  // front left wheel (clockwise)
#define LPWM_1 5  // front right wheel (anticlockwise)
// Wheel B
#define RPWM_2 6  // front right wheel
#define LPWM_2 7
// Wheel C
#define RPWM_3 8  // rear left wheel
#define LPWM_3 9
// Wheel D
#define RPWM_4 10  // rear right wheel
#define LPWM_4 11

// Encoder input pins
// The below are interrupt pins
#define ENC_1A 2
#define ENC_2A 3
#define ENC_3A 18
#define ENC_4A 19
// Then the other pins which are not interrupt pins
#define ENC_1B 28
#define ENC_2B 29
#define ENC_3B 30
#define ENC_4B 31


// [DEVELOPMENT] Remote control pins
#define N_CONTROL 22 // forward push button
#define S_CONTROL 23 // reverse push button
#define E_CONTROL 24 // left strafe push button
#define W_CONTROL 25 // right strafe push button

#endif