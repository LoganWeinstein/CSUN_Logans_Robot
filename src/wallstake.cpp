#include "main.h"
#include "subsystems.hpp"
#include "lemlib/pid.hpp"
#include "lemlib/timer.hpp"
#include <cstdlib>
#include <iostream>

// Define target positions in raw rotation sensor units (motor degrees or ticks)
constexpr int point1 = 0; // point1 is always the limit switch (base position)
int point2 = 2550; // customizable load position
int point3 = 15500; // customizable score position

// PID controller
lemlib::PID wallstakePID(2, 0, 0, 2, false);
bool isPIDRunning = false;

// Wallstake movement states
enum WALLSTAKE_STATE { BASE_STATE, LOAD_STATE, SCORE_STATE };
WALLSTAKE_STATE current_state = BASE_STATE; // default after hitting limit switch

void moveTo(WALLSTAKE_STATE state, int max_error = 20, int timeout = 2000) {
    constexpr int base_location = point1;
    int load_location = point2;
    int score_location = point3;

    int target;
    switch (state) {
        case BASE_STATE:
            wallstake.move(-100);
            while (!limitswitch.get_value()) {
            pros::delay(10);
            }
            wallstake.move(0);
            wallstake_sensor.reset_position();
            current_state = BASE_STATE;
            return;
        case LOAD_STATE:
            target = load_location;
            break;
        case SCORE_STATE:
            target = score_location;
            conveyor.move(-127);
            pros::delay(75);
            conveyor.move(0);
            break;
    }

    wallstakePID.reset();
    lemlib::Timer timer(timeout);
    isPIDRunning = true;

    while (true) {
        if (limitswitch.get_value() == false) {
            wallstake.move(0);
            current_state = BASE_STATE;
            break;
        }

        // PID logic based on wallstake_sensor
        int error = target - wallstake_sensor.get_position();
        double output = wallstakePID.update(error);
        wallstake.move_voltage(output);

        // Exit if close enough or timeout
        if (std::abs(error) < max_error || timer.isDone()) {
            wallstake.move(0);
            isPIDRunning = false;
            current_state = state;
            break;
        }
    }
}

// Driver control wrapper
void wallstakecontrol() {
    if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R2) && !isPIDRunning) {
        if (current_state == LOAD_STATE) {
            moveTo(SCORE_STATE);
        } else {
            moveTo(LOAD_STATE);
        }
    }

    if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_A)) {
        moveTo(BASE_STATE);
    }
}

//Autonomous ---------------------------------------------------------

void wallstake_lower_to_limit() {
    wallstake.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    wallstake.move(-100);
    while (!limitswitch.get_value()) {
        pros::delay(10);
    }
    wallstake.move(0);
    pros::delay(50);
    wallstake_sensor.reset_position();
}

void wallstake_auton() {
    wallstake_lower_to_limit();

    // Move to point1 and place preload
    moveTo(LOAD_STATE);
    pros::delay(700);
    conveyor.move(127); 
    pros::delay(1000);
  
    // Move to point2 after placing 
    moveTo(SCORE_STATE);
    conveyor.move(-127);
    pros::delay(75);
    conveyor.move(0);
    pros::delay(1000);
}



// // Define positions (in motor degrees)
// const int point1 = 20;
// const int point2 = 180;

// const double rotationScale = 0.09; // Adjust this based on calibration (e.g., 1000 ticks = 10 degrees)

// // State tracker
// bool isMoving = false;
// bool initialized = false;
// int cycleState = 0;
// int targetPosition = 0;

// double getCorrectedAngle() {
//   return wallstake_sensor.get_angle() * rotationScale;
// }

// void moveToPosition(int target) {
// int speed = 70;
  
//   while (true) {
//     wallstake.move(speed);
//     if ((speed > 0 && getCorrectedAngle() >= target) || (speed < 0 && getCorrectedAngle() <= target)) {
//         break;
//     }
//     pros::delay(10);
// }
// }

// bool hasReachedTarget(int target) {
//   return std::abs(getCorrectedAngle() - target) < 5;
// }

// // Non-blocking wallstake control to run as a background task
// void wallstakecontrol() {

//   wallstake.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);

//   // Initial check: if not at limit switch, lower until it is
//   if (!limitswitch.get_value()) {
//     wallstake.move(-70);
//     while (!limitswitch.get_value()) {
//       pros::delay(10);
//     }
//     wallstake.move(0);
//     pros::delay(50);
//     wallstake_sensor.reset();
//     isMoving = false;
//     targetPosition = point1;
//   } else {
//     wallstake.move(0);
//     pros::delay(50);
//     wallstake_sensor.reset();
//     isMoving = false;
//     targetPosition = point1;
//   }
  
//   // Moved outside of faulty block
//   // Initialization complete
//   // Initialization complete
//   initialized = true;

//   while (true) {
//     // A: Force move to limit switch regardless
//     if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_A)) {
//         wallstake.move(-70);
//         while (!limitswitch.get_value()) {
//           pros::delay(10);
//         }
//         wallstake.move(0);
//         pros::delay(50);
//         wallstake_sensor.reset();
//         isMoving = false;
//         cycleState = 0;
//     }


// // R2: Cycle between point1, point2, and point3
//     if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R2) && !isMoving) {
//       switch (cycleState) {
//         case 0:
//           targetPosition = point1;
//           break;
//         case 1:
//           targetPosition = point2;
//           conveyor.move(-127);
//           pros::delay(75);
//           conveyor.move(0);
//           break;
//       }

//       moveToPosition(targetPosition);
//       cycleState = (cycleState + 1) % 2;
//     }

//     // Check if motor reached target
//     if (isMoving && hasReachedTarget(targetPosition)) {
//       isMoving = false;
//       pros::delay(100);

//       if (targetPosition == point1) {
//         wallstake.move(10); // Light hold at point1
//       } else {
//         wallstake.move(0); // Use brake hold for point2 and point3
//       }
//     }

//     pros::delay(10); // main loop delay
//   }
 
// }



// // Autonomous wallstake control sequence --------------------------------------------
// void wallstake_lower_to_limit() {
//   wallstake.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
//   wallstake.move(-100);
//   while (!limitswitch.get_value()) {
//       pros::delay(10);
//   }
//   wallstake.move(0);
//   pros::delay(50);
//   wallstake_sensor.reset_position();
// }

// void wallstake_auton() {
//   wallstake.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);

//   // Move to point1 and place preload
//   moveToPosition(point1);
//     pros::delay(700);
//   conveyor.move(127); 

//   // Move to point2 after placing 
//   moveToPosition(point2);
//   conveyor.move(-127);
//   pros::delay(75);
//   conveyor.move(0);
//   pros::delay(1000);
// }
