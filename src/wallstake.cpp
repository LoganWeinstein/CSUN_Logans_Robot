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
const int basePos = 0;
const int loadPos = 2200;
const int scorePos = 19250;

void wallstakecontrol() {
    wallstake.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);

    // Initial reset using limit switch
    if (!limitswitch.get_value()) {
        wallstake.move(-100);
        while (!limitswitch.get_value()) pros::delay(5);
        wallstake.move(0);
        pros::delay(50);
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
            int target = 0;

            if (currentState == BASE) {
                wallstake.move(-100);
                while (!limitswitch.get_value()) pros::delay(5);
                wallstake.move(0);
                pros::delay(30);
                wallstake_sensor.reset_position();

                // Skip PID since we're already at base
                lastState = currentState;
                continue;
            } else if (currentState == LOAD) {
                target = loadPos;
            } else if (currentState == SCORE) {
                target = scorePos;
            }

            wallPID.reset();
            lemlib::Timer timer(700); // 0.7 sec timeout

            while (true) {
                double error = target - wallstake_sensor.get_position();
                double voltage = wallPID.update(error);
                wallstake.move_voltage(voltage);

                if (std::abs(error) < 5 || timer.isDone()) break;

                pros::delay(5); // faster PID loop
            }

            if (target == loadPos) {
                wallstake.move(10); // slight hold
            } else {
                wallstake.move(0);
            }

            pros::delay(10); // minimal delay before accepting new input
            lastState = currentState;
        }

        pros::delay(5);
    }
}


// Autonomous wallstake control sequence

void wallstake_lower_to_limit() {
    if (!limitswitch.get_value()) {
        wallstake.move(-100);
        while (!limitswitch.get_value()) pros::delay(5);
        wallstake.move(0);
        pros::delay(50);
        wallstake_sensor.reset_position();
    }
    else {
    wallstake.move(0);
    pros::delay(50);
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
    wallstake.move(10);
    pros::delay(400);
    conveyor.move(127);
    pros::delay(1000);

    // Step 3: Move to point2 with simultaneous conveyor jerk
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
    wallstake.move(0);
}