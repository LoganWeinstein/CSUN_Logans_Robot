#include "main.h"
#include "subsystems.hpp"

void hookauton(int speed) {
    if (speed > 0) {
        hook.move(speed);  
    }   
    if (speed < 0) {
        hook.move(speed);
    }  
    if (speed = 0) {
        hook.move(0); 
    }
}  

double hookDirection = 0;
bool hookRunningUp = false;
bool hookRunningDown = false;
bool hookSlowedDown = false;
uint32_t upStartTime = 0;
uint32_t downStartTime = 0;

void hookcontrol() {
    // L2 pressed → go up for 1 second
    if (controller.get_digital_new_press(DIGITAL_L2)) {
        hookRunningUp = true;
        hookRunningDown = false;
        hookSlowedDown = false;
        upStartTime = pros::millis();
        hookDirection = 0.5; // go up at 50%
    }

    // L1 pressed → go down, slow after 1 second
    if (controller.get_digital_new_press(DIGITAL_L1)) {
        hookRunningDown = true;
        hookRunningUp = false;
        hookSlowedDown = false;
        downStartTime = pros::millis();
        hookDirection = -0.5; // start down at 50%
    }

    // Going UP: stop after 1 sec
    if (hookRunningUp && pros::millis() - upStartTime >= 300) {
        hookRunningUp = false;
        hookDirection = 0;
    }

    // Going DOWN: change to 20% after 1 sec
    if (hookRunningDown && !hookSlowedDown && pros::millis() - downStartTime >= 500) {
        hookDirection = -0.1; // reduce speed
        hookSlowedDown = true;
    }

    // Send motor command
    hook.move(hookDirection * 127);
}
