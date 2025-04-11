#include "main.h"
#include "subsystems.hpp"
#include "pros/optical.h"

bool detection_enabled = false;
bool yPressedLast = false; // Track previous Y button state

void setColorDetectionEnabled(bool enabled) {
    detection_enabled = enabled;
    if (enabled) {
        eye.set_led_pwm(100); // Turn light on at full brightness
    } else {
        eye.set_led_pwm(0);   // Turn light off
    }
}

// Use this in autonomous: returns true if a ring was detected and stops conveyor for 50ms
// Automatically resets after 300ms so next call can detect again
bool detectAndPauseIfRing() {
    static bool waitingForDetection = true;

    if (!waitingForDetection) return false;

    if (eye.get_proximity() > 150) {
        int hue = eye.get_hue();
        if ((hue >= 0 && hue <= 25) || (hue >= 150 && hue <= 230)) {
            conveyor.move(0);
            pros::delay(10);
            waitingForDetection = false;

            // Background task to reset after delay
            pros::Task([=]() {
                pros::delay(200);
                waitingForDetection = true;
            });

            return true;
        }
    }
    return false;
}

void objectDetectionTask(void* param) {
    while (true) {
        // Toggle logic for Y button
        bool yPressedNow = controller.get_digital(pros::E_CONTROLLER_DIGITAL_Y);
        if (yPressedNow && !yPressedLast) {
            setColorDetectionEnabled(!detection_enabled);
        }
        yPressedLast = yPressedNow;

        if (!detection_enabled) {
            pros::delay(5);
            continue;
        }

        // Only do detection if conveyor is already running forward
        if (eye.get_proximity() > 150 && conveyor.get_actual_velocity() > 0) {
            int hue = eye.get_hue();

            // Blue ring: jerk the conveyor back quickly and resume
            if (hue >= 150 && hue <= 230) {
                pros::delay(135);
                conveyor.move(0);
                pros::delay(300);
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
