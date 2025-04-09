#include "main.h"
#include "subsystems.hpp"

// Define positions (in motor degrees)
const int point1 = 230;
const int point2 = 1000;

// State tracker
bool isMoving = false;
bool initialized = false;
bool goToPoint1 = true;
// Removed pressCount, using goToPoint1 instead
int targetPosition = 0;

void moveToPosition(int target) {
  wallstake.move_absolute(target, 127);
  isMoving = true;
}

bool hasReachedTarget(int target) {
  return std::abs(wallstake.get_position() - target) < 5;
}

// Non-blocking wallstake control to run as a background task
void wallstakecontrol() {
  wallstake.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);

  // Initial check: if not at limit switch, lower until it is
  if (!limitswitch.get_value()) {
    wallstake.move(-127);
    while (limitswitch.get_value()) {
      pros::delay(10);
    }
    wallstake.move(0); // Stop after hitting limit switch
    wallstake.tare_position(); // Reset position to 0 at limit
    goToPoint1 = true; // Ensure it starts by going to point1
  }
  initialized = true;

  while (true) {
    // A: Force move to limit switch regardless
    if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_A)) {
      wallstake.move(-127);
      int timeout = 250; // give up after 0.5 seconds just in case
      int elapsed = 0;
      while (!limitswitch.get_value() && elapsed < timeout) {
        pros::delay(10);
        elapsed += 10;
      }
      wallstake.move(0);
      if (limitswitch.get_value()) {
        wallstake.move(0);
        pros::delay(100);             // Allow motor to settle
        wallstake.tare_position();             // Fully stop             // Stop after taring
        isMoving = false;
        goToPoint1 = true; // Reset toggle so next press goes to point1
      }
    }

    // R2: Alternate between point1 and point2
    if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R2) && !isMoving) {
      if (goToPoint1) {
        targetPosition = point1;
      } else {
        targetPosition = point2;
        conveyor.move(-127); // Briefly reverse conveyor before moving to point2
        pros::delay(75);
        conveyor.move(0);
      }

      moveToPosition(targetPosition);
      goToPoint1 = !goToPoint1;
    }

    // Check if motor reached target
    if (isMoving && hasReachedTarget(targetPosition)) {
      isMoving = false;
      pros::delay(100);
      wallstake.move(0);

      // Optional: add visual or audio feedback here
      if (targetPosition == point1) {
        wallstake.move(10); // Hold lightly at point1
      }
    }

      // Hook retract at point2
    // Removed duplicate conveyor control block
    }

    pros::delay(20);
}


/// Autonomous Section -----------------------------------------------------

void wallstake_lower_to_limit() {
  wallstake.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
  wallstake.move(-100);
  while (!limitswitch.get_value()) {
    pros::delay(10);
  }
  wallstake.move(0);
  wallstake.tare_position();
}

void wallstake_move_to_point1() {
  wallstake.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
  wallstake.move_absolute(point1, 127);
  while (std::abs(wallstake.get_position() - point1) > 10) {
    pros::delay(10);
  }
  wallstake.move(0);
}

void wallstake_move_to_point2() {
  wallstake.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
  wallstake.move_absolute(point2, 127);
  while (std::abs(wallstake.get_position() - point2) > 10) {
    pros::delay(10);
  }
  conveyor.move(-127);
  pros::delay(100);
  conveyor.move(0);
  wallstake.move(0);
}

void wallstake_auton() {
  wallstake_lower_to_limit();
  wallstake_move_to_point1();
  pros::delay(300);
  intake.move(127);
  conveyor.move(127);
  pros::delay(1000);
  intake.move(0);
  conveyor.move(0);
  wallstake_move_to_point2();
  pros::delay(700);
  wallstake_move_to_point1();
}
