#include "main.h"
#include "lemlib/api.hpp"

#include "subsystems.hpp"
#include "autons.hpp"

#include "intake.hpp"
#include "wallstake.hpp"
#include "bullrush.hpp"
#include "hook.hpp"
#include "color.hpp"

ASSET(matchstart2_txt);

//Skills auton (right side) -------------------------------------------------------------------
void skillsright() {

chassis.setPose(24, -55.5, 180);

hookauton(110); 
pros::delay(200);
hookauton(0);

//Get mobile goal 
chassis.moveToPose(56, -12, -135, 4000, {.forwards = false,  .maxSpeed = 70, .minSpeed = 50});
chassis.waitUntilDone();

hookauton(-127);
intakeauton(127); 
conveyorauton(127);  

pros::delay(200);

chassis.moveToPose(48, -45, 180, 4000, {.forwards = true, .maxSpeed = 127, .minSpeed = 110});
chassis.waitUntilDone();

hookauton(-30);

//Get corner
chassis.moveToPose(63.5, -60, 135, 3000, {.forwards = true, .lead = 0.55, .maxSpeed = 90, .minSpeed = 70});
chassis.waitUntilDone();

pros::delay(1000);

chassis.moveToPose(48, -45, 135, 4000, {.forwards = false, .maxSpeed = 127, .minSpeed = 110,});
chassis.waitUntilDone();

//Get middle ring and score on aliance stake
chassis.moveToPose(0, -48, -90, 4000, { .forwards = true, .lead = 0.15, .maxSpeed = 127, .minSpeed = 110,}, true);
wallstake_lower_to_limit();

while (!detectAndPauseIfRing()) {
    pros::delay(10); // check every 10ms
}

chassis.moveToPose(0, -55,180, 4000, {.forwards = true , .maxSpeed = 110, .minSpeed = 100,});
chassis.waitUntilDone();

wallstake_auton();

    // chassis.turnToHeading(45, 1000);
    // chassis.waitUntil(3);

chassis.moveToPose(24, -24, 0, 3000, {.forwards = true, .maxSpeed = 127, .minSpeed = 110,});
chassis.waitUntilDone();
chassis.moveToPose(4, -4, -45, 3000, {.forwards = true, .maxSpeed = 127, .minSpeed = 110,});
chassis.waitUntilDone();
chassis.moveToPose(24, -24, -45, 3000, {.forwards = false, .maxSpeed = 127, .minSpeed = 110,});
chassis.waitUntilDone();

//Get middle line rings
chassis.moveToPose(45, 0, 90, 3000, {.forwards = true, .lead = 0.05, .maxSpeed = 70, .minSpeed = 50,});
chassis.waitUntilDone();
chassis.moveToPose(68, 3, 80, 3000, {.forwards = true, .lead = 0.05, .maxSpeed = 70, .minSpeed = 50,});
chassis.waitUntilDone();

//Put mobile goal in corner
chassis.moveToPose(56, -57, -45, 5000, {.forwards = false, .lead = 0.2, .maxSpeed = 127, .minSpeed = 110,});
pros::delay(1000);
intakeauton(0); 
conveyorauton(0);
chassis.waitUntilDone();

hookauton(110);
pros::delay(280);
hookauton(0);

pros::delay(500);

//Drive to 2nd Mobile Goal 
chassis.moveToPose(48, -24, 0, 4000, {.forwards = true, .lead = 0.2, .maxSpeed = 127, .minSpeed = 110,});
chassis.waitUntilDone();
chassis.moveToPose(24, 24, -45, 4000, {.forwards = true, .lead = 0.3, .maxSpeed = 127, .minSpeed = 110,});
chassis.waitUntilDone();

intakeauton(127);  
conveyorauton(127);

//Get Center Ring first 
chassis.moveToPose(0, 0, -135, 4000, {.forwards = true, .lead = 0.3, .maxSpeed = 127, .minSpeed = 110,});
chassis.waitUntilDone();

//Get 3 red rings on 2nd mobile goal 
chassis.moveToPose(48, 24, 90, 4000, {.forwards = true, .lead = 0.2, .maxSpeed = 127, .minSpeed = 110,});
chassis.waitUntilDone();
chassis.moveToPose(48, 48, 0, 4000, {.forwards = true, .lead = 0.2, .maxSpeed = 127, .minSpeed = 110,});
chassis.waitUntilDone();
chassis.moveToPose(24, 48, -90, 4000, {.forwards = true, .lead = 0.2, .maxSpeed = 127, .minSpeed = 110,});
chassis.waitUntilDone();

//Go to corner and get both rings
chassis.moveToPose(56, 57, 45, 4000, {.forwards = true, .lead = 0.3, .maxSpeed = 127, .minSpeed = 110,}); 
chassis.waitUntilDone();
chassis.moveToPose(52, 52, 45, 4000, {.forwards = false, .lead = 0.3, .maxSpeed = 127, .minSpeed = 110,});
chassis.waitUntilDone();
chassis.moveToPose(56, 57, 45, 4000, {.forwards = true, .lead = 0.3, .maxSpeed = 127, .minSpeed = 110,});
chassis.waitUntilDone();
chassis.moveToPose(50, 50, 45, 4000, {.forwards = false, .lead = 0.3, .maxSpeed = 127, .minSpeed = 110,});
chassis.waitUntilDone();

//Turn and put mobile goal in corner
chassis.turnToHeading(-135, 1000);
chassis.waitUntil(4);
chassis.moveToPose(56, 57, -135, 4000, {.forwards = false, .lead = 0.3, .maxSpeed = 127, .minSpeed = 110,});
pros::delay(200);
intakeauton(0);  
conveyorauton(0);
chassis.waitUntilDone();

hookauton(110);
pros::delay(280);
hookauton(0);

pros::delay(500);

//Go to rings and back alliance stake
chassis.moveToPose(0, 55.5, -90, 4000, {.forwards = true, .lead = 0.2, .maxSpeed = 127, .minSpeed = 110,});
pros::delay(400);
intakeauton(127);  
chassis.waitUntilDone();

chassis.moveToPose(15, 58, 130, 4000, {.forwards = false, .lead = 0.3, .maxSpeed = 127, .minSpeed = 110,});
chassis.waitUntilDone();

}




//Match Auton -----------------------------------------------------------------------------------------------------
void matchright() {

chassis.follow(matchstart2_txt, 10, 4000, true);

}