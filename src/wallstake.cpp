#pragma once

#include "main.h"
#include "subsystems.hpp"
#include "lemlib/pid.hpp"
#include "lemlib/timer.hpp"
#include <cmath>

// --- Wallstake PID controller ---
lemlib::PID wallPID(5, 0, 30);  // kP, kI, kD

// --- Target Positions ---
const double basePos = 0;
const double loadPos = 2200;
const double scorePos = 19250;
const double corner_get = 24000;
const double corner_drop = 30000;
const double ladder = 15000;

// --- State tracking ---
enum WallState { BASE, LOAD, SCORE };
WallState currentState = BASE;
int holdTarget = basePos;
bool holdingPosition = false;

// --- Lower to Limit ---
void wallstake_lower_to_limit() {
    wallstake.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    if (!limitswitch.get_value()) {
        wallstake.move(-70);
        while (!limitswitch.get_value()) pros::delay(5);
        wallstake.move(0);
        pros::delay(50);
        wallstake_sensor.reset_position();
    } else {
        wallstake.move(0);
        wallstake_sensor.reset_position();
    }
}

// --- Wallstake Control Task ---
void wallstakecontrol() {
    wallstake_lower_to_limit();
    WallState lastState = BASE;

    while (true) {
        if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_A)) {
            currentState = BASE;
        }

        if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R2)) {
            if (currentState == BASE) currentState = LOAD;
            else if (currentState == LOAD) currentState = SCORE;
            else if (currentState == SCORE) currentState = LOAD;
        }

        if (currentState != lastState) {
            if (currentState == BASE) {
                wallstake_lower_to_limit();
                holdTarget = basePos;
                lastState = currentState;
                continue;
            } else if (currentState == LOAD) {
                holdTarget = loadPos;
            } else if (currentState == SCORE) {
                pros::Task([]() {
                    conveyor.move(-127);
                    uint32_t startTime = pros::millis();
                    while (pros::millis() - startTime < 200) pros::delay(5);
                    conveyor.move(0);
                });
                holdTarget = scorePos;
            }

            wallPID.reset();
            lemlib::Timer timer(700);

            while (true) {
                double error = holdTarget - wallstake_sensor.get_position();
                double voltage = wallPID.update(error);
                wallstake.move_voltage(voltage);
                if (std::abs(error) < 5 || timer.isDone()) break;
                pros::delay(5);
            }

            pros::delay(10);
            holdingPosition = true;
            lastState = currentState;
        }

        if (holdingPosition) {
            double error = holdTarget - wallstake_sensor.get_position();
            double voltage = wallPID.update(error);
            wallstake.move_voltage(voltage);
        }

        pros::delay(5);
    }
}

// --- Autonomous Routines ---
void wallstake_auton() {
    wallPID.reset();
    lemlib::Timer timer1(700);
    while (true) {
        double error = 1600 - wallstake_sensor.get_position();
        double voltage = wallPID.update(error);
        wallstake.move_voltage(voltage);
        if (std::abs(error) < 5 || timer1.isDone()) break;
        pros::delay(5);
    }
    holdTarget = 1600;
    holdingPosition = true;
    pros::delay(400);

    conveyor.move(127);
    pros::delay(1000);

    lemlib::Timer timer2(700);
    conveyor.move(-127);
    pros::delay(75);
    conveyor.move(0);

    while (true) {
        double error = scorePos - wallstake_sensor.get_position();
        double voltage = wallPID.update(error);
        wallstake.move_voltage(voltage);
        if (std::abs(error) < 5 || timer2.isDone()) break;
        pros::delay(5);
    }
    holdTarget = scorePos;
    holdingPosition = true;
}

// --- Background PID Task Wrapper ---
void wallstake_move_and_hold_task(void* param) {
    double target = *static_cast<double*>(param);

    wallstake.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    wallPID.reset();
    lemlib::Timer timer(700);

    while (true) {
        double error = target - wallstake_sensor.get_position();
        double voltage = wallPID.update(error);
        wallstake.move_voltage(voltage);
        if (std::abs(error) < 5 || timer.isDone()) break;
        pros::delay(5);
    }

    while (true) {
        double error = target - wallstake_sensor.get_position();
        double voltage = wallPID.update(error);
        wallstake.move_voltage(voltage);
        pros::delay(5);
    }
}

// --- Corner Ring Functions ---
void wallstake_cornerget() {
    static double target = corner_get;
    pros::c::task_create(wallstake_move_and_hold_task, &target, TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "corner_get");
}

void wallstake_cornerdrop() {
    static double target = corner_drop;
    pros::c::task_create(wallstake_move_and_hold_task, &target, TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "corner_drop");
}

void wallstake_touch_ladder() {
    static double target = ladder;
    pros::c::task_create(wallstake_move_and_hold_task, &target, TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "ladder_touch");
}