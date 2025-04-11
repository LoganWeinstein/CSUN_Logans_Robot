#include "main.h"
#include "subsystems.hpp"

// Define positions (in motor degrees)
const int point1 = 140;
const int point2 = 550;
const int point3 = 1000;

// State tracker
bool isMoving = false;
bool initialized = false;
int cycleState = 0;
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
    wallstake.move(-70);
    pros::delay(1500);
    wallstake.move(0);
    pros::delay(50);
    wallstake.tare_position();
    isMoving = false;
    targetPosition = point1;
  } else {
    wallstake.move(0);
    pros::delay(50);
    wallstake.tare_position();
    isMoving = false;
    targetPosition = point1;
  }
  
  // Moved outside of faulty block
  // Initialization complete
  // Initialization complete
  initialized = true;

  while (true) {
    // A: Force move to limit switch regardless
    if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_A)) {
        wallstake.move(-90);
        while (!limitswitch.get_value()) {
          pros::delay(10);
        }
        wallstake.move(0);
        pros::delay(100);
        wallstake.tare_position();
        isMoving = false;
        cycleState = 0;
    }


// R2: Cycle between point1, point2, and point3
    if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R2) && !isMoving) {
      switch (cycleState) {
        case 0:
          targetPosition = point1;
          break;
        case 1:
          targetPosition = point2;
          conveyor.move(-127);
          pros::delay(75);
          conveyor.move(0);
          break;
        case 2:
          targetPosition = point3;
          break;
      }

      moveToPosition(targetPosition);
      cycleState = (cycleState + 1) % 3;
    }

    // Check if motor reached target
    if (isMoving && hasReachedTarget(targetPosition)) {
      isMoving = false;
      pros::delay(100);

      if (targetPosition == point1) {
        wallstake.move(5); // Light hold at point1
      } else {
        wallstake.move(0); // Use brake hold for point2 and point3
      }
    }

    pros::delay(10); // main loop delay
  }
 
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

void wallstake_move_to_point2_and_3() {
  wallstake.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);

  // Move to point 2 at full speed
  wallstake.move_absolute(point2, 127);
  conveyor.move(-127);
  pros::delay(100);
  conveyor.move(0);
  while (std::abs(wallstake.get_position() - point2) > 10) {
    pros::delay(10);
  }

  // Move to point 3 at slower speed
  wallstake.move_absolute(point3, 50);
  while (std::abs(wallstake.get_position() - point3) > 10) {
    pros::delay(10);
  }

  wallstake.move(0);
}

void wallstake_auton() {
  wallstake_move_to_point1();
  pros::delay(500);
  conveyor.move(127);
  pros::delay(800);
  conveyor.move(0);
  wallstake_move_to_point2_and_3();
  pros::delay(800);
}
