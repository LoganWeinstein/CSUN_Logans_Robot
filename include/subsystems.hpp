#pragma once

#include "api.h"
#include "pros/motors.hpp"
#include "lemlib/api.hpp"
#include "pros/rotation.hpp"

extern lemlib::Chassis chassis;
extern pros::Controller controller;

inline pros::Motor intake(7);
inline pros::MotorGroup conveyor({9,-10}); 
inline pros::Motor bullrush(19);
inline pros::Motor hook(-11);
inline pros::Motor wallstake(16); 

inline pros::Optical eye(18);
inline pros::Rotation wallstake_sensor(-12); 


inline pros::adi::DigitalIn limitswitch('A');
//Radio in port 20



// Your motors, sensors, etc. should go here.  Below are examples

// inline pros::Motor intake(1);
// inline pros::adi::DigitalIn limit_switch('A');