#include "main.h"
#include "subsystems.hpp"


void bullrushauton() {
    bullrush.move(-127);
    pros::delay(200); 
    bullrush.move(-30);
    pros::delay(1000);
    bullrush.move(50);
    pros::delay(700);
    bullrush.move(0);
  }

int bullrushTimer1 = 0;
int bullrushTimer2 = 0;
bool bullrushSpeed = false;

void bullrushcontrol() {
  while (true) {
    if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_Y)) {
      bullrush.move(-127);
      bullrushTimer1 = pros::millis();
      bullrush.move(-30);

    } else if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_B)) {
      bullrush.move(90);
      bullrushTimer2 = pros::millis();
      bullrush.move(0);
    }

    // Hold at lower speed after 200ms 
    if (pros::millis() - bullrushTimer1 >= 200) {
      bullrush.move(0);
    }

    if (pros::millis() - bullrushTimer2 >= 300) {
      bullrush.move(0);
    }


    pros::delay(10);
  }
}

