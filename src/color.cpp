#include "main.h"
#include "subsystems.hpp"
#include "pros/optical.h"

// === COLOR FLAGS ===
bool detectRed = false;
bool detectBlue = true;  // set this one to true for blue detection

// --- Utility: check for red ---
bool isRed(int hue) {
    return hue >= 0 && hue <= 25;
}

// --- Utility: check for blue ---
bool isBlue(int hue) {
    return hue >= 150 && hue <= 230;
}

// --- Detect either red or blue (used in auton) ---
bool detectAndPauseIfRing() {
    static bool waitingForDetection = true;
    if (!waitingForDetection) return false;

    if (eye.get_proximity() > 150) {
        int hue = eye.get_hue();
        if (isRed(hue) || isBlue(hue)) {
            conveyor.move(0);
            pros::delay(5);
            waitingForDetection = false;

            pros::Task([=]() {
                pros::delay(50);
                waitingForDetection = true;
            });

            return true;
        }
    }
    return false;
}

// --- Background detection task (detectRed or detectBlue based on param) ---
// CALL THIS: pros::Task detectionTask(objectDetectionTask, &detectBlue);  // or &detectRed

void objectDetectionTask(void* param) {
    bool* colorFlag = static_cast<bool*>(param);
    bool detectRedMode = (colorFlag == &detectRed);
    bool detectBlueMode = (colorFlag == &detectBlue);

    eye.set_led_pwm(100);  // LED always on

    while (true) {
        if (eye.get_proximity() > 150 && conveyor.get_actual_velocity() > 0) {
            int hue = eye.get_hue();

            if (*colorFlag && detectRedMode && isRed(hue)) {
                pros::delay(135);
                conveyor.move(0);
                pros::delay(300);
                conveyor.move(127);
            }
            else if (*colorFlag && detectBlueMode && isBlue(hue)) {
                pros::delay(135);
                conveyor.move(0);
                pros::delay(300);
                conveyor.move(127);
            }
        }
        pros::delay(20);
    }
}
