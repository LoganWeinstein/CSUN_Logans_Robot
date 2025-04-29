#include "main.h"
#include "subsystems.hpp"
#include "pros/optical.h"

// ====== CONFIGURATION ======
constexpr bool detectRed = false;  // set to false to detect blue
// ===========================

bool detection_enabled = false;
bool yPressedLast = false; // Track previous Y button state

void setColorDetectionEnabled(bool enabled) { //ENABLE COLOR DETECTION, Starts off 
    detection_enabled = enabled;
    if (enabled) {
        eye.set_led_pwm(100); // Turn light on at full brightness
    } else {
        eye.set_led_pwm(0);   // Turn light off
    }
}

// Automatically resets after 300ms so next call can detect again
bool detectAndPauseIfRing() {
    static bool waitingForDetection = true;

    if (!waitingForDetection) return false;

    if (eye.get_proximity() > 150) {
        int hue = eye.get_hue();
        if ((hue >= 0 && hue <= 25) || (hue >= 150 && hue <= 230)) {
            conveyor.move(0);
            pros::delay(5);
            waitingForDetection = false;

            // Background task to reset after delay
            pros::Task([=]() {
                pros::delay(50);
                waitingForDetection = true;
            });

            return true;
        }
    }
    return false;
}

void objectDetectionTask(void* param) {
    while (true) {
        // Toggle detection with X button
        bool yPressedNow = controller.get_digital(pros::E_CONTROLLER_DIGITAL_X);
        if (yPressedNow && !yPressedLast) {
            detection_enabled = !detection_enabled;
            setColorDetectionEnabled(detection_enabled);
            controller.rumble(detection_enabled ? "." : "..");
        }
        yPressedLast = yPressedNow;

        if (!detection_enabled) {
            pros::delay(5);
            continue;
        }

        // Detection only when conveyor is running forward
        if (eye.get_proximity() > 150 && conveyor.get_actual_velocity() > 0) {
            int hue = eye.get_hue();

            bool isTargetColor = detectRed
                ? (hue >= 0 && hue <= 25)
                : (hue >= 150 && hue <= 230);

            if (isTargetColor) {
                pros::delay(135);
                conveyor.move(0);
                pros::delay(300);
                conveyor.move(127);  // Resume forward motion
            }
        }

        pros::delay(20);
    }
}
