#include "main.h"
#include "subsystems.hpp"

void hookauton(int speed) {
    if (speed > 0) {
        hook.move(speed);
    } else if (speed < 0) {
        hook.move(speed);
    } else if (speed == 0) {
        hook.move(0);
    }
}

double hookDirection = 0;
bool hookRunningUp = false;
bool hookRunningDown = false;
bool hookSlowedDown = false;
bool conveyorOverride = false;
uint32_t upStartTime = 0;
uint32_t downStartTime = 0;

void hookcontrol() {
    if (controller.get_digital_new_press(DIGITAL_L2)) {
        hookRunningUp = true;
        hookRunningDown = false;
        hookSlowedDown = false;
        upStartTime = pros::millis();
        hookDirection = 0.5;
        conveyorOverride = true;
    }

    if (controller.get_digital_new_press(DIGITAL_L1)) {
        hookRunningDown = true;
        hookRunningUp = false;
        hookSlowedDown = false;
        downStartTime = pros::millis();
        hookDirection = -0.5;
    }

    if (hookRunningUp && pros::millis() - upStartTime >= 300) {
        hookRunningUp = false;
        hookDirection = 0;
        conveyorOverride = false;
    }

    if (hookRunningDown && !hookSlowedDown && pros::millis() - downStartTime >= 500) {
        hookDirection = -0.1;
        hookSlowedDown = true;
    }

    hook.move(hookDirection * 127);

    if (conveyorOverride) {
        conveyor.move(-100);
    }
}
