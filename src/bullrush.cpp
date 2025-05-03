#include "main.h"
#include "subsystems.hpp"


void bullrushdown() {
    bullrush.move(-127);
    
  }

void bullrushcorner() {
    bullrush.move(-127);
    pros::delay(280);
    bullrush.move(0);
  }

void bullrushup() {
    bullrush.move(127);
    pros::delay(600); 
    bullrush.move(0);
  }

  bool bullrushActiveY = false;
  bool bullrushActiveB = false;
  int bullrushTimerY = 0;
  int bullrushTimerB = 0;
  
  void bullrushcontrol() {
    while (true) {
      if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_Y)) {
        bullrush.move(-127); // Fast retract
        bullrushTimerY = pros::millis();
        bullrushActiveY = true;
        bullrushActiveB = false;
      }
  
      if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_B)) {
        bullrush.move(90); // Extend
        bullrushTimerB = pros::millis();
        bullrushActiveB = true;
        bullrushActiveY = false;
      }
  
      // After 200ms of Y press, switch to slower hold power
      if (bullrushActiveY && pros::millis() - bullrushTimerY >= 500) {
        bullrush.move(-70);
        bullrushActiveY = false;
      }
  
      // After 300ms of B press, stop
      if (bullrushActiveB && pros::millis() - bullrushTimerB >= 600) {
        bullrush.move(0);
        bullrushActiveB = false;
      }
  
      pros::delay(10);
    }
  }
  