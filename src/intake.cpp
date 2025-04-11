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

bool intakeRunning = false; // Tracks if intake is running forward

void intakecontrol() {
  // Toggle forward intake/conveyor on R1
  if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R1)) {
    if (!intakeRunning) {
      intake.move(127);
      conveyor.move(127);
    } else {
      intake.move(0);
      conveyor.move(0);
    }
    intakeRunning = !intakeRunning;
  }
}

