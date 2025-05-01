#pragma once

#include "lemlib/pid.hpp"

// PID controller state
extern lemlib::PID wallstakePID;
extern bool isPIDRunning;

// Wallstake movement states
enum WALLSTAKE_STATE { BASE_STATE, LOAD_STATE, SCORE_STATE };
extern WALLSTAKE_STATE current_state;

// Target positions
constexpr int point1 = 0; // limit switch reset position
extern int point2;           // load position
extern int point3;           // score position

// Function declarations
void moveTo(WALLSTAKE_STATE state, int max_error = 20, int timeout = 2000);
void wallstake_lower_to_limit();
void wallstake_auton();
void wallstakecontrol();
void wallstake_cornerget();
void wallstake_cornerdrop();
void wallstake_touch_ladder();







