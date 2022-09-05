#include <control_allocation.h>

// Converting from Robocock movement to wheel speeds (in rad/s)
WheelSpeeds calculateWheelSpeeds(RobocockMovement m) {
    WheelSpeeds s; // create a new WheelSpeeds object
    s.av_A = (-m.vx - m.vy) / (RW * sqrt2) + m.av * RO / RW;
    s.av_B = (m.vx - m.vy) / (RW * sqrt2) + m.av * RO / RW;
    s.av_C = (-m.vx + m.vy) / (RW * sqrt2) + m.av * RO / RW;
    s.av_D = (m.vx + m.vy) / (RW * sqrt2) + m.av * RO / RW;
}