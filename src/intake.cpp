#include "main.h"
#include "subsystems.hpp"

void intakeauton(int speed) {
    if (speed > 0) {
        intake.move(speed);
    } else if (speed < 0) {
        intake.move(speed);
    } else if (speed == 0) {
        intake.move(0);
    }
}

void conveyorauton(int speed) {
  if (speed > 0) {
      conveyor.move(speed);
  } else if (speed < 0) {
      conveyor.move(speed);
  } else if (speed == 0) {
      conveyor.move(0);
  }
}

void intakecontrol() {
  static bool intakeToggled = false;

  // Toggle forward intake/conveyor on R1 press
  if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R1)) {
      intakeToggled = !intakeToggled;
  }

  // Hold Y to reverse intake/conveyor (overrides toggle)
  if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_Y)) {
      intake.move(-127);
      conveyor.move(-127);
  } 
  // Toggle forward mode if Y is not held
  else if (intakeToggled) {
      intake.move(127);
      conveyor.move(127);
  } 
  // Stop if neither toggle nor Y is active
  else {
      intake.move(0);
      conveyor.move(0);
  }
}
