#include "main.h"
#include "subsystems.hpp"


void bullrushauton() {
    bullrush.move(-127);
    pros::delay(1000); // Run for 1 second
    bullrush.move(127);
    pros::delay(200);
    bullrush.move(0);
}

int bullrushTimer = 0;
int bullrushSpeed = 0;

void bullrushcontrol() {
  while (true) {
    if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_Y)) {
      bullrush.move(-127);
      bullrushTimer = pros::millis();
      bullrushSpeed = -127;
    } else if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_B)) {
      bullrush.move(127);
      bullrushTimer = pros::millis();
      bullrushSpeed = 127;
    }

    // Stop after 1 second
    if (bullrushSpeed != 0 && pros::millis() - bullrushTimer > 1000) {
      bullrush.move(0);
      bullrushSpeed = 0;
    }

    pros::delay(10);
  }
}

