#include "main.h"
#include "subsystems.hpp"
#include "pros/optical.h"
#include "color.hpp"

// === Global Enum Constants ===
ColorTarget Red = ColorTarget::RED;
ColorTarget Blue = ColorTarget::BLUE;

// === Manual toggle control ===
bool colorDetectionEnabled = true;
bool xPressedLast = false;

bool ringDetectedAuton = false; 


// === Jerk timer control ===
bool jerk = false;
uint32_t jerkStartTime = 0;
bool lastDetection = false;  // For rising edge detection

// --- Color detection ranges ---
bool isRed(int hue) {
    return hue >= 0 && hue <= 25;
}
bool isBlue(int hue) {
    return hue >= 150 && hue <= 230;
}

// --- Detect either red or blue in auton ---
bool waitForRingDetection(int timeout) {
    uint32_t start = pros::millis();
    bool waitingForClear = false;

    while ((pros::millis() - start) < timeout) {
        int prox = eye.get_proximity();
        int hue = eye.get_hue();

        bool detected = (prox >= 150);

        if (waitingForClear) {
            if (!detected) waitingForClear = false;
        } else if (detected) {
            conveyor.move(0);
            pros::delay(50);
            return true;
        }

        pros::delay(5);
    }

    return false;
}



// --- Continuous object detection task ---
void objectDetectionTask(void* param) {
    ColorTarget* target = static_cast<ColorTarget*>(param);
    eye.set_led_pwm(100);  // LED on by default

    while (true) {
        // Toggle detection with X button
        bool xPressedNow = controller.get_digital(pros::E_CONTROLLER_DIGITAL_X);
        if (xPressedNow && !xPressedLast) {
            colorDetectionEnabled = !colorDetectionEnabled;
            eye.set_led_pwm(colorDetectionEnabled ? 100 : 0);
            controller.rumble(colorDetectionEnabled ? "." : "..");
        }
        xPressedLast = xPressedNow;

        if (!colorDetectionEnabled) {
            pros::delay(10);
            continue;
        }

        // Ring detection logic
        if (eye.get_proximity() > 150) {
            int hue = eye.get_hue();
            bool isTargetDetected = (*target == ColorTarget::RED && isRed(hue)) ||
                                    (*target == ColorTarget::BLUE && isBlue(hue));

            // Rising edge: only trigger jerk when detection goes from false to true
            if (isTargetDetected && !jerk && !lastDetection) {
                jerkStartTime = pros::millis();
                jerk = true;
            }

            lastDetection = isTargetDetected;
        } else {
            lastDetection = false;  // Proximity too low
        }

        // Run jerk logic
        if (jerk) {
            uint32_t elapsed = pros::millis() - jerkStartTime;

            if (elapsed < 175) {
                conveyor.move(127);  // Run normally
            } else if (elapsed < 225) {
                conveyor.move(-50);    // Pause briefly
            } else {
                conveyor.move(127);  // Resume after pause
                jerk = false;
            }
        }

        pros::delay(10);  // Prevent CPU overload
    }
}
