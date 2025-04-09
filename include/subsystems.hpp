#pragma once

#include "api.h"
#include "pros/motors.hpp"

extern pros::Controller controller;

inline pros::Motor intake(7);
inline pros::MotorGroup conveyor({8,-9}); 
inline pros::Motor bullrush(10);
inline pros::Motor hook(-11);
inline pros::MotorGroup wallstake({12,-19}); 

inline pros::Optical eye(18);

inline pros::adi::DigitalIn limitswitch('A');
//Radio in port 20



// Your motors, sensors, etc. should go here.  Below are examples

// inline pros::Motor intake(1);
// inline pros::adi::DigitalIn limit_switch('A');