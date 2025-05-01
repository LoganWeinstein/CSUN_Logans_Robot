#include "main.h"
#include "subsystems.hpp"       
#include <cmath>  
#include "lemlib/pid.hpp"
#include "lemlib/timer.hpp"

// State tracking
enum WallState { BASE, LOAD, SCORE };
WallState currentState = BASE;

// PID controller for wallstake
lemlib::PID wallPID(5, 0, 30);  // Adjust kP, kI, kD as needed

// Target positions (raw rotation sensor values)
const double basePos = 0;
const double loadPos = 1100;
const double scorePos = 19250;

int holdTarget = basePos;
bool holdingPosition = false;

void wallstakecontrol() {
    wallstake.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);

    // Initial reset using limit switch
    if (!limitswitch.get_value()) {
        wallstake.move(-100);
        while (!limitswitch.get_value()) pros::delay(5);
        wallstake.move(0);
        pros::delay(50);
        wallstake_sensor.reset_position();
    } else {
        wallstake.move(0);
        wallstake_sensor.reset_position();
    }

    WallState lastState = BASE;

    while (true) {
        // Button A forces reset to BASE
        if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_A)) {
            currentState = BASE;
        }

        // R2 cycles: BASE → LOAD → SCORE → LOAD → SCORE ...
        if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R2)) {
            if (currentState == BASE) currentState = LOAD;
            else if (currentState == LOAD) currentState = SCORE;
            else if (currentState == SCORE) currentState = LOAD;
        }

        // Only act if the state changed
        if (currentState != lastState) {
            if (currentState == BASE) {
                if (!limitswitch.get_value()) {
                    wallstake.move(-100);
                    while (!limitswitch.get_value()) pros::delay(5);
                    wallstake.move(0);
                    pros::delay(30);
                }
                wallstake_sensor.reset_position();
                holdTarget = basePos;
                lastState = currentState;
                continue;
            } else if (currentState == LOAD) {
                holdTarget = loadPos;
            } else if (currentState == SCORE) {
                pros::Task([]() {
                    conveyor.move(-127);
                    uint32_t startTime = pros::millis();
                    while (pros::millis() - startTime < 200) {
                        pros::delay(5);
                    }
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

        // Maintain holding position
        if (holdingPosition) {
            double error = holdTarget - wallstake_sensor.get_position();
            double voltage = wallPID.update(error);
            wallstake.move_voltage(voltage);
        }

        pros::delay(5);
    }
}

void wallstake_lower_to_limit() {
    if (!limitswitch.get_value()) {
        wallstake.move(-100);
        while (!limitswitch.get_value()) pros::delay(5);
        wallstake.move(0);
        pros::delay(50);
        wallstake_sensor.reset_position();
    } else {
        wallstake.move(0);
        wallstake_sensor.reset_position();
    }
}

double loadPos2 = 2500;

void wallstake_auton() {
    wallPID.reset();
    lemlib::Timer timer1(700);
    while (true) {
        double error = loadPos2 - wallstake_sensor.get_position();
        double voltage = wallPID.update(error);
        wallstake.move_voltage(voltage);
        if (std::abs(error) < 5 || timer1.isDone()) break;
        pros::delay(5);
    }
    holdTarget = loadPos2;
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

// Corner Rings Auton Functions -------------------------------------------------
double corner_get = 30000;
double corner_drop = 35000; //Adjust values
double ladder = 15000;

void wallstake_cornerget() {
    wallstake.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    wallPID.reset();
    lemlib::Timer timer3(700);
    while (true) {
        double error = corner_get - wallstake_sensor.get_position();
        double voltage = wallPID.update(error);
        wallstake.move_voltage(voltage);

        if (std::abs(error) < 5 || timer3.isDone()) break;
        pros::delay(5);
    }
    holdTarget = corner_get;
    holdingPosition = true;
}

void wallstake_cornerdrop() {
    wallstake.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    wallPID.reset();
    lemlib::Timer timer4(700);
    while (true) {
        double error = corner_drop - wallstake_sensor.get_position();
        double voltage = wallPID.update(error);
        wallstake.move_voltage(voltage);

        if (std::abs(error) < 5 || timer4.isDone()) break;
        pros::delay(5);
    }
    holdTarget = corner_drop;
    holdingPosition = true;
}

void wallstake_touch_ladder() {
    wallstake.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    wallPID.reset();
    lemlib::Timer timer3(700);
    while (true) {
        double error = ladder - wallstake_sensor.get_position();
        double voltage = wallPID.update(error);
        wallstake.move_voltage(voltage);

        if (std::abs(error) < 5 || timer3.isDone()) break;
        pros::delay(5);
    }
    holdTarget = ladder;
    holdingPosition = true;
}
