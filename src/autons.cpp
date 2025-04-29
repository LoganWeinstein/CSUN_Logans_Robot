#include "autons.hpp"
#include "main.h"
#include "lemlib/api.hpp"
#include "subsystems.hpp"

#include "intake.hpp"
#include "wallstake.hpp"
#include "bullrush.hpp"
#include "hook.hpp"
#include "color.hpp"

<<<<<<< HEAD

//ASSET(matchstart2_txt);
void matchright() {


}

void skillsright() {
=======
void skills_right() {
>>>>>>> f8b19ba4b51ecf1d59ccefbacafd3da4e199b54d

chassis.setPose(0, -58.5, 0);

wallstake_lower_to_limit();

intakeauton(127); 
conveyorauton(100);

//Get Middle Ring and Score on Alliance Stake
chassis.moveToPoint(0, -48, 3000, {.forwards = true, .maxSpeed = 70,}, true); //Async (moves on)
chassis.waitUntilDone();

while (!detectAndPauseIfRing()) {
    pros::delay(2); // check every 2ms
}

chassis.turnToHeading(180, 1000, {.maxSpeed = 110,});
chassis.waitUntilDone();

chassis.moveToPoint(0, -55, 3000, {.forwards = true, .maxSpeed = 127,}, true); //Async (moves on)
chassis.waitUntilDone();

wallstake_auton();

hookauton(30);
conveyorauton(127);

chassis.moveToPoint(0, -50, 3000, {.forwards = false, .maxSpeed = 100,}, true);
chassis.waitUntilDone();

//Get 1st mobile goal ------------------------
hookauton(40);
pros::delay(200);
conveyorauton(127);

chassis.moveToPose(40, -30, -130, 2500, {.forwards = false, .lead = 0.2, .maxSpeed = 90,}); // Add last mintue slew
pros::delay(500);
wallstake_lower_to_limit();
chassis.waitUntilDone();

chassis.moveToPose(50, -22, -130, 3000, {.forwards = false, .maxSpeed = 50,});
chassis.waitUntilDone();

hookauton(-127);

pros::delay(150);

//Get middle line of rings ---------------------
chassis.moveToPose(45, 0, 0, 3000, {.forwards = true, .maxSpeed = 127,});
hookauton(-40);
chassis.waitUntilDone();


chassis.moveToPose(45, -20, 0, 3000, {.forwards = false, .maxSpeed = 127});
chassis.waitUntilDone();

chassis.moveToPose(26, -26, -110, 3000, {.forwards = true, .lead = 0.5, .maxSpeed = 127});
chassis.waitUntilDone();

chassis.moveToPose(4, -4, -45, 3000, {.forwards = true, .lead = 0.1, .maxSpeed = 127,});
chassis.waitUntilDone();

chassis.moveToPose(4, 8, 0, 3000, {.forwards = true, .lead = 0.05, .maxSpeed = 127,});
chassis.waitUntilDone(); 

//Get two rings and put mobile goal in corner
chassis.moveToPose(10, -10, 0, 3000, {.forwards = false, .lead = 0.1, .maxSpeed = 127,});
pros::delay(500);
conveyorauton(-127);
pros::delay(400);
conveyorauton(127);
chassis.waitUntil(9);
chassis.moveToPose(24, -24, -45, 3000, {.forwards = false, .lead = 0.4, .maxSpeed = 127,});
chassis.waitUntilDone();
chassis.turnToHeading(135, 1000);
chassis.waitUntil(2);
chassis.moveToPose(56, -59, 135, 3000, {.forwards = true, .lead =0.2, .maxSpeed = 90});
chassis.waitUntilDone();
chassis.moveToPose(48, -48, 135, 3000, {.forwards = false, .maxSpeed = 127,});
chassis.waitUntilDone();
chassis.turnToHeading(-45, 1000);
chassis.waitUntil(2);
chassis.moveToPose(56, -59, -45, 5000, {.forwards = false, .lead = 0.2, .maxSpeed = 127,});
pros::delay(300);
intakeauton(0); 
conveyorauton(0);
chassis.waitUntilDone();

conveyorauton(-90);
hookauton(100);
pros::delay(250);
hookauton(10);
conveyorauton(0);

pros::delay(500);

//Drive to middle rings and get load both (blue and red)
chassis.moveToPose(53, 16, 0, 4000, {.forwards = true, .maxSpeed = 127,}, true);
intakeauton(127); 
conveyorauton(127);
chassis.waitUntilDone(); //async

while (!detectAndPauseIfRing()) {
    pros::delay(5); // check every 5ms
}

intakeauton(0);

chassis.moveToPose(60, 0, 0, 3000, {.forwards = false, .maxSpeed = 127,});
chassis.waitUntilDone();

chassis.turnToHeading(90, 1000);
chassis.waitUntilDone();

wallstake_lower_to_limit();

pros::delay(500);

wallstake_auton(); //Double wallstake 

wallstake_lower_to_limit();

wallstake_auton();

//Go to 2nd mobile goal
chassis.moveToPose(24, 24, -45, 3000, {.forwards = true, .lead = 0.3, .maxSpeed = 127,});
pros::delay(400);
wallstake_lower_to_limit();
chassis.waitUntilDone();

hookauton(-127);

pros::delay(150);



}


void matchred_posright() {
chassis.setPose(50, -24, 33);

//Get right mobile goal 
chassis.moveToPose(38, -16, 33, 4000, {.forwards = true, .lead = 0.05, .maxSpeed = 127,});
chassis.waitUntil(10);
bullrushauton();
chassis.waitUntilDone();

chassis.moveToPose(34.5, -27, 33, 4000, {.forwards = false, .maxSpeed = 127,});
chassis.waitUntilDone();

chassis.turnToHeading(213, 1000);
chassis.waitUntilDone();

chassis.moveToPose(38, -16, 213, 3000, {.forwards = false, .maxSpeed = 60,}); 
chassis.waitUntilDone();

//Get Two rings and corner rings (Color sensor on)
chassis.moveToPose(48, -24, 90, 3000, {.forwards = true, .maxSpeed = 100,}); 
chassis.waitUntilDone();
chassis.moveToPose(48, -48, 180, 3000, {.forwards = true, .maxSpeed = 100,}); 
chassis.waitUntilDone();

chassis.moveToPose(56, -59, 135, 3000, {.forwards = true, .maxSpeed = 127,}); 
chassis.waitUntil(40);
wallstake_cornerget();
chassis.waitUntilDone();











}



void matchred_poscenter() {




}

