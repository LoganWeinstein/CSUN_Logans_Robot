#include "main.h"
#include "subsystems.hpp"
#include "pros/optical.h"

bool detection_enabled = false;

void setColorDetectionEnabled(bool enabled) {
    detection_enabled = enabled;
}

void objectDetectionTask(void* param) {
    while (true) {
        if (!detection_enabled) {
            pros::delay(20);
            continue;
        }

        // Only do detection if conveyor is already running forward
        if (eye.get_proximity() > 150 && conveyor.get_actual_velocity() > 0) {
            int hue = eye.get_hue();

            // Blue ring: jerk the conveyor back quickly and resume
            if (hue >= 150 && hue <= 230) {
                // pros::delay(150);
                conveyor.move(0);
                pros::delay(1000);
                conveyor.move(127);  // Resume forward motion
            }

            // Red ring: just print it, let it flow through
            else if (hue >= 0 && hue <= 25) {
                // No interruption, just a label
            }
        }

        pros::delay(20);
    }
}
