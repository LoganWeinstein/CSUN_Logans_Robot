#include "main.h"
#include "subsystems.hpp"
#include <algorithm>

// Define target positions in degrees
const int point1 = 20;
const int point2 = 180;

// State variables
bool isMoving = false;
bool initialized = false;
int cycleState = 0;
int targetPosition = 0;

// Check if target is reached (within ±7 degrees)
bool hasReachedTarget(int target) {
  return std::abs(wallstake_sensor.get_angle() - target) < 7;
}

// Move motor using simplified proportional control until sensor reaches target
void moveToPosition(int target) {
  isMoving = true;

  while (std::abs(wallstake_sensor.get_angle() - target) > 3) { // 3° tolerance
      int direction = (wallstake_sensor.get_angle() < target) ? 1 : -1;
      wallstake.move(direction * 70); // fixed speed toward target
      pros::delay(10);
  }

  wallstake.move(0); 
  isMoving = false;
}

// Main wallstake control task
void wallstakecontrol() {
  wallstake.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);

  // Initial reset to bottom via limit switch
  if (!limitswitch.get_value()) {
    wallstake.move(-70);
    while (!limitswitch.get_value()) pros::delay(10);
  }
  wallstake.move(0);
  pros::delay(50);
  wallstake_sensor.reset_position();
  isMoving = false;
  targetPosition = point1;
  initialized = true;

  while (true) {
    // Manual reset with A button
    if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_A)) {
      wallstake.move(-70);
      while (!limitswitch.get_value()) pros::delay(10);
      wallstake.move(0);
      pros::delay(50);
      wallstake_sensor.reset_position();
      isMoving = false;
      cycleState = 0;
    }

    // R2 cycles between point1 and point2
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
      }
      moveToPosition(targetPosition);
      cycleState = (cycleState + 1) % 2;
    }

    pros::delay(10);
  }
}

// Autonomous wallstake control sequence --------------------------------------------
void wallstake_auton() {
  wallstake.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);

  // Lower to limit switch to zero the sensor
  wallstake.move(-100);
  while (!limitswitch.get_value()) {
    pros::delay(10);
  }
  wallstake.move(0);
  wallstake_sensor.reset_position();
  pros::delay(100);

  // Move to point1, place preload
  moveToPosition(point1);
  

  // Wait for ring detection
  while (true) {
    if (eye.get_proximity() > 150) {
      int hue = eye.get_hue();
      if ((hue >= 0 && hue <= 25) || (hue >= 150 && hue <= 230)) {
        conveyor.move(0);
        break;
      }
    }
    pros::delay(10);
  }

  pros::delay(500);
  conveyor.move(127);

  // Move to point2 after placing
  moveToPosition(point2);
  conveyor.move(-127);
  pros::delay(75);
  conveyor.move(0);
  pros::delay(1000);
} 
