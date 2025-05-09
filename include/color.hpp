#pragma once

enum class ColorTarget { RED, BLUE };

extern ColorTarget Red;
extern ColorTarget Blue;

void objectDetectionTask(void* param);
bool detectAndPauseIfRing();

bool waitForRingDetection(int timeout);
// extern bool ringDetectedAuton; 
// void ringDetectionTaskAuton(void* param);

