<<<<<<< HEAD
=======
#include "autons.hpp"
>>>>>>> 53fd74a816273b2edebe95cfef86e7018ced41e4
#include "main.h"
#include "lemlib/api.hpp"

#include "subsystems.hpp"
#include "autons.hpp"

#include "intake.hpp"
#include "wallstake.hpp"
#include "bullrush.hpp"
#include "hook.hpp"
#include "color.hpp"

<<<<<<< HEAD
//ASSET(matchstart2_txt);


void skillsRnew() {

chassis.setPose(0, -58.5, 0);

wallstake_lower_to_limit();

intakeauton(100); 
conveyorauton(127);

//Get Middle Ring and Score on Alliance Stake
chassis.moveToPoint(0, -48, 3000, {.forwards = true, .maxSpeed = 127,}, true); //Async (moves on)
chassis.waitUntilDone();

while (!detectAndPauseIfRing()) {
    pros::delay(5); // check every 5ms
}

chassis.turnToHeading(180, 3000, {.maxSpeed = 110,});
chassis.waitUntilDone();

wallstake_auton();

hookauton(90); 
pros::delay(200);
hookauton(10);


//Get 1st mobile goal 

chassis.moveToPose(53, -19, -130, 4000, {.forwards = false,  .maxSpeed = 90});
pros::delay(500);
wallstake_lower_to_limit();
chassis.waitUntilDone();

hookauton(-90);

//Get middle line of rings
chassis.moveToPose(48, 0, 0, 3000, {.forwards = true, .lead = 0.1, .maxSpeed = 127,});
hookauton(-40);
chassis.waitUntilDone();

//Get 3 rings
chassis.moveToPose(48, -12, 0, 3000, {.forwards = false, .maxSpeed = 127});
chassis.waitUntilDone();

chassis.moveToPose(24, -24, -110, 3000, {.forwards = true, .maxSpeed = 127});
chassis.waitUntilDone();

chassis.moveToPose(4, -2, -45, 3000, {.forwards = true, .lead = 0.1, .maxSpeed = 127,});
chassis.waitUntilDone();

chassis.moveToPose(4, 3, -30, 3000, {.forwards = true, .lead = 0.05, .maxSpeed = 127,});
chassis.waitUntilDone(); 

//Get two rings and put mobile goal in corner
chassis.moveToPose(30, -25, -45, 3000, {.forwards = false, .lead = 0.1, .maxSpeed = 127,});
chassis.waitUntilDone();
chassis.moveToPose(48, -48, 135, 3000, {.forwards = true, .lead = 0.2, .maxSpeed = 127,});
chassis.waitUntilDone();
chassis.moveToPose(60, -56.5, 135, 3000, {.forwards = true, .maxSpeed = 90});
chassis.waitUntilDone();
chassis.moveToPose(48, -48, 135, 3000, {.forwards = false, .maxSpeed = 127,});
chassis.waitUntilDone();
chassis.turnToHeading(-45, 1000);
chassis.waitUntil(2);
chassis.moveToPose(56, -57, -45, 5000, {.forwards = false, .lead = 0.2, .maxSpeed = 127,});
pros::delay(300);
intakeauton(0); 
conveyorauton(0);
chassis.waitUntilDone();

hookauton(100);
pros::delay(300);
hookauton(10);

pros::delay(500);

//Drive to middle rings
chassis.moveToPose(60, 14, 0, 4000, {.forwards = true, .maxSpeed = 127,}, true);
intakeauton(127); 
conveyorauton(127);
chassis.waitUntilDone(); //async

while (!detectAndPauseIfRing()) {
    pros::delay(5); // check every 5ms
}

chassis.moveToPose(60, 0, 0, 3000, {.forwards = false, .maxSpeed = 127,});
chassis.waitUntilDone();

chassis.turnToHeading(90, 1000);
chassis.waitUntilDone();

wallstake_lower_to_limit();

pros::delay(500);

wallstake_auton();

//Go to 2nd mobile goal
chassis.moveToPose(24, 24, -45, 3000, {.forwards = true, .lead = 0.3, .maxSpeed = 127,});
pros::delay(400);
wallstake_lower_to_limit();
chassis.waitUntilDone();

}

//Skills auton (right side) -------------------------------------------------------------------
void skillsright() {

=======
ASSET(matchstart2_txt);

void skillsrightNEW() {

    chassis.setPose(0, -58.5, 0);
    
    wallstake_lower_to_limit();
    
    intakeauton(100); 
    conveyorauton(127);
    
    //Get Middle Ring and Score on Alliance Stake
    chassis.moveToPoint(0, -48, 3000, {.forwards = true, .maxSpeed = 127,}, true); //Async (moves on)
    chassis.waitUntilDone();
    
    while (!detectAndPauseIfRing()) {
        pros::delay(5); // check every 5ms
    }
    
    chassis.turnToHeading(180, 3000, {.maxSpeed = 110,});
    chassis.waitUntilDone();
    
    wallstake_auton();
    
    hookauton(90); 
    pros::delay(200);
    hookauton(10);
    
    
    //Get 1st mobile goal 
    
    chassis.moveToPose(53, -19, -130, 4000, {.forwards = false,  .maxSpeed = 90});
    pros::delay(500);
    wallstake_lower_to_limit();
    chassis.waitUntilDone();
    
    hookauton(-90);
    
    //Get middle line of rings
    chassis.moveToPose(48, 0, 0, 3000, {.forwards = true, .lead = 0.1, .maxSpeed = 127,});
    hookauton(-40);
    chassis.waitUntilDone();
    
    //Get 3 rings
    chassis.moveToPose(48, -12, 0, 3000, {.forwards = false, .maxSpeed = 127});
    chassis.waitUntilDone();
    
    chassis.moveToPose(24, -24, -110, 3000, {.forwards = true, .maxSpeed = 127});
    chassis.waitUntilDone();
    
    chassis.moveToPose(4, -2, -45, 3000, {.forwards = true, .lead = 0.1, .maxSpeed = 127,});
    chassis.waitUntilDone();
    
    chassis.moveToPose(4, 3, -30, 3000, {.forwards = true, .lead = 0.05, .maxSpeed = 127,});
    chassis.waitUntilDone(); 
    
    //Get two rings and put mobile goal in corner
    chassis.moveToPose(30, -25, -45, 3000, {.forwards = false, .lead = 0.1, .maxSpeed = 127,});
    chassis.waitUntilDone();
    chassis.moveToPose(48, -48, 135, 3000, {.forwards = true, .lead = 0.2, .maxSpeed = 127,});
    chassis.waitUntilDone();
    chassis.moveToPose(60, -56.5, 135, 3000, {.forwards = true, .maxSpeed = 90});
    chassis.waitUntilDone();
    chassis.moveToPose(48, -48, 135, 3000, {.forwards = false, .maxSpeed = 127,});
    chassis.waitUntilDone();
    chassis.turnToHeading(-45, 1000);
    chassis.waitUntil(2);
    chassis.moveToPose(56, -57, -45, 5000, {.forwards = false, .lead = 0.2, .maxSpeed = 127,});
    pros::delay(300);
    intakeauton(0); 
    conveyorauton(0);
    chassis.waitUntilDone();
    
    hookauton(100);
    pros::delay(300);
    hookauton(10);
    
    pros::delay(500);
    
    //Drive to middle rings
    chassis.moveToPose(60, 14, 0, 4000, {.forwards = true, .maxSpeed = 127,}, true);
    intakeauton(127); 
    conveyorauton(127);
    chassis.waitUntilDone(); //async
    
    while (!detectAndPauseIfRing()) {
        pros::delay(5); // check every 5ms
    }
    
    chassis.moveToPose(60, 0, 0, 3000, {.forwards = false, .maxSpeed = 127,});
    chassis.waitUntilDone();
    
    chassis.turnToHeading(90, 1000);
    chassis.waitUntilDone();
    
    wallstake_lower_to_limit();
    
    pros::delay(500);
    
    wallstake_auton();
    
    //Go to 2nd mobile goal
    chassis.moveToPose(24, 24, -45, 3000, {.forwards = true, .lead = 0.3, .maxSpeed = 127,});
    pros::delay(400);
    wallstake_lower_to_limit();
    chassis.waitUntilDone();
    
    }

void skillsright() {
>>>>>>> 53fd74a816273b2edebe95cfef86e7018ced41e4
chassis.setPose(24, -55.5, 180);

hookauton(110); 
pros::delay(200);
hookauton(0);

//Get mobile goal 
<<<<<<< HEAD
chassis.moveToPose(56, -12, -130, 4000, {.forwards = false,  .maxSpeed = 70, .minSpeed = 50});
=======
chassis.moveToPose(56, -12, -130, 4000, {.forwards = false,  .maxSpeed = 70});
>>>>>>> 53fd74a816273b2edebe95cfef86e7018ced41e4
chassis.waitUntilDone();

hookauton(-127);
intakeauton(127); 
conveyorauton(127);  

pros::delay(200);

<<<<<<< HEAD
chassis.moveToPose(48, -45, 180, 4000, {.forwards = true, .maxSpeed = 127, .minSpeed = 110});
=======
chassis.moveToPose(48, -45, 180, 4000, {.forwards = true, .maxSpeed = 127});
>>>>>>> 53fd74a816273b2edebe95cfef86e7018ced41e4
chassis.waitUntilDone();

hookauton(-50);

//Get corner
<<<<<<< HEAD
chassis.moveToPose(60, -56.5, 135, 3000, {.forwards = true, .lead = 0.55, .maxSpeed = 90, .minSpeed = 70});
=======
chassis.moveToPose(60, -56.5, 135, 3000, {.forwards = true, .lead = 0.55, .maxSpeed = 90});
>>>>>>> 53fd74a816273b2edebe95cfef86e7018ced41e4
chassis.waitUntilDone();

pros::delay(1000);

<<<<<<< HEAD
chassis.moveToPose(48, -48, 135, 4000, {.forwards = false, .maxSpeed = 127, .minSpeed = 110,});
chassis.waitUntilDone();

chassis.turnToHeading(-90, 2000, {.direction = AngularDirection::CW_CLOCKWISE, .maxSpeed = 127, .minSpeed = 110,});
chassis.waitUntilDone();

//Get middle ring and score on aliance stake
chassis.moveToPose(-8, -48, -90, 5000, {.forwards = true, .maxSpeed = 127, .minSpeed = 110,});
=======
chassis.moveToPose(48, -48, 135, 4000, {.forwards = false, .maxSpeed = 127});
chassis.waitUntilDone();

chassis.turnToHeading(-90, 2000, {.direction = AngularDirection::CW_CLOCKWISE, .maxSpeed = 127});
chassis.waitUntilDone();

//Get middle ring and score on aliance stake
chassis.moveToPose(-8, -48, -90, 5000, {.forwards = true, .maxSpeed = 127});
>>>>>>> 53fd74a816273b2edebe95cfef86e7018ced41e4
while (!detectAndPauseIfRing()) {
    pros::delay(5); // check every 10ms
}
chassis.waitUntilDone();

// wallstake_lower_to_limit();

<<<<<<< HEAD
chassis.moveToPose(0, -48, -90, 4000, { .forwards = false, .lead = 0.1, .maxSpeed = 127, .minSpeed = 110});
chassis.waitUntilDone();
chassis.turnToHeading(180, 2000, {.direction = AngularDirection::CCW_COUNTERCLOCKWISE, .maxSpeed = 127, .minSpeed = 110});
chassis.waitUntil(2);
chassis.moveToPoint(0, -55, 4000, { .forwards = true, .maxSpeed = 50, .minSpeed = 30,});
=======
chassis.moveToPose(0, -48, -90, 4000, { .forwards = false, .lead = 0.1, .maxSpeed = 127});
chassis.waitUntilDone();
chassis.turnToHeading(180, 2000, {.direction = AngularDirection::CCW_COUNTERCLOCKWISE, .maxSpeed = 127});
chassis.waitUntil(2);
chassis.moveToPoint(0, -55, 4000, { .forwards = true, .maxSpeed = 50});
>>>>>>> 53fd74a816273b2edebe95cfef86e7018ced41e4
chassis.waitUntilDone();

wallstake_auton();

// wallstake_lower_to_limit();

conveyorauton(127);

//Get Center Ring
<<<<<<< HEAD
chassis.moveToPose(24, -24, 0, 3000, {.forwards = true, .lead = 0.5, .maxSpeed = 127, .minSpeed = 30,});
chassis.waitUntilDone();
chassis.moveToPose(4, -2, -45, 3000, {.forwards = true, .lead = 0.1, .maxSpeed = 127, .minSpeed = 110,});
=======
chassis.moveToPose(24, -24, 0, 3000, {.forwards = true, .lead = 0.5, .maxSpeed = 127});
chassis.waitUntilDone();
chassis.moveToPose(4, -2, -45, 3000, {.forwards = true, .lead = 0.1, .maxSpeed = 127});
>>>>>>> 53fd74a816273b2edebe95cfef86e7018ced41e4
chassis.waitUntilDone();

pros::delay(500);
conveyorauton(-90);

<<<<<<< HEAD
chassis.moveToPose(24, -24, -45, 3000, {.forwards = false, .maxSpeed = 127, .minSpeed = 110,});
=======
chassis.moveToPose(24, -24, -45, 3000, {.forwards = false, .maxSpeed = 127});
>>>>>>> 53fd74a816273b2edebe95cfef86e7018ced41e4
chassis.waitUntilDone();

conveyorauton(127);

//Get middle line rings
<<<<<<< HEAD
chassis.moveToPose(45, 0, 90, 3000, {.forwards = true, .lead = 0.05, .maxSpeed = 70, .minSpeed = 50,});
chassis.waitUntilDone();
chassis.moveToPose(63, 3, 80, 3000, {.forwards = true, .lead = 0.05, .maxSpeed = 70, .minSpeed = 50,});
chassis.waitUntilDone();

//Put mobile goal in corner
chassis.moveToPose(56, -57, -45, 5000, {.forwards = false, .lead = 0.2, .maxSpeed = 127, .minSpeed = 110,});
=======
chassis.moveToPose(45, 0, 90, 3000, {.forwards = true, .lead = 0.05, .maxSpeed = 70});
chassis.waitUntilDone();
chassis.moveToPose(63, 3, 80, 3000, {.forwards = true, .lead = 0.05, .maxSpeed = 70});
chassis.waitUntilDone();

//Put mobile goal in corner
chassis.moveToPose(56, -57, -45, 5000, {.forwards = false, .lead = 0.2, .maxSpeed = 127});
>>>>>>> 53fd74a816273b2edebe95cfef86e7018ced41e4
pros::delay(1000);
intakeauton(0); 
conveyorauton(0);
chassis.waitUntilDone();

hookauton(110);
pros::delay(280);
hookauton(0);

pros::delay(500);

//Drive to 2nd Mobile Goal make forward to back transition 
<<<<<<< HEAD
chassis.moveToPose(40, 0, 0, 4000, {.forwards = true, .lead = 0.2, .maxSpeed = 127, .minSpeed = 110,});
hookauton(50);
chassis.waitUntilDone();
chassis.moveToPose(13, 30, -45, 5000, {.forwards = false, .lead = 0.2, .maxSpeed = 60, .minSpeed = 30,});
=======
chassis.moveToPose(40, 0, 0, 4000, {.forwards = true, .lead = 0.2, .maxSpeed = 127});
hookauton(50);
chassis.waitUntilDone();
chassis.moveToPose(13, 30, -45, 5000, {.forwards = false, .lead = 0.2, .maxSpeed = 60});
>>>>>>> 53fd74a816273b2edebe95cfef86e7018ced41e4
chassis.waitUntil(2);

pros::delay(800);
hookauton(-110);
pros::delay(300);

intakeauton(127);  
conveyorauton(127);

//Get Center Ring first 
<<<<<<< HEAD
chassis.moveToPose(0, 0, -135, 4000, {.forwards = true, .lead = 0.3, .maxSpeed = 127, .minSpeed = 110,});
=======
chassis.moveToPose(0, 0, -135, 4000, {.forwards = true, .lead = 0.3, .maxSpeed = 127});
>>>>>>> 53fd74a816273b2edebe95cfef86e7018ced41e4
chassis.waitUntilDone();

hookauton(-60);

//Get 3 red rings on 2nd mobile goal 
<<<<<<< HEAD
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
=======
chassis.moveToPose(48, 24, 90, 4000, {.forwards = true, .lead = 0.2, .maxSpeed = 127});
chassis.waitUntilDone();
chassis.moveToPose(48, 48, 0, 4000, {.forwards = true, .lead = 0.2, .maxSpeed = 127});
chassis.waitUntilDone();
chassis.moveToPose(24, 48, -90, 4000, {.forwards = true, .lead = 0.2, .maxSpeed = 127});
chassis.waitUntilDone();

//Go to corner and get both rings
chassis.moveToPose(56, 57, 45, 4000, {.forwards = true, .lead = 0.3, .maxSpeed = 127}); 
chassis.waitUntilDone();
chassis.moveToPose(52, 52, 45, 4000, {.forwards = false, .lead = 0.3, .maxSpeed = 127});
chassis.waitUntilDone();
chassis.moveToPose(56, 57, 45, 4000, {.forwards = true, .lead = 0.3, .maxSpeed = 127});
chassis.waitUntilDone();
chassis.moveToPose(50, 50, 45, 4000, {.forwards = false, .lead = 0.3, .maxSpeed = 127});
>>>>>>> 53fd74a816273b2edebe95cfef86e7018ced41e4
chassis.waitUntilDone();

//Turn and put mobile goal in corner
chassis.turnToHeading(-135, 1000);
chassis.waitUntil(4);
<<<<<<< HEAD
chassis.moveToPose(56, 57, -135, 4000, {.forwards = false, .lead = 0.3, .maxSpeed = 127, .minSpeed = 110,});
=======
chassis.moveToPose(56, 57, -135, 4000, {.forwards = false, .lead = 0.3, .maxSpeed = 127});
>>>>>>> 53fd74a816273b2edebe95cfef86e7018ced41e4
pros::delay(200);
intakeauton(0);  
conveyorauton(0);
chassis.waitUntilDone();

hookauton(110);
pros::delay(280);
hookauton(0);

pros::delay(500);

//Go to rings and back alliance stake
<<<<<<< HEAD
chassis.moveToPose(0, 55.5, -90, 4000, {.forwards = true, .lead = 0.2, .maxSpeed = 127, .minSpeed = 110,});
=======
chassis.moveToPose(0, 55.5, -90, 4000, {.forwards = true, .lead = 0.2, .maxSpeed = 127});
>>>>>>> 53fd74a816273b2edebe95cfef86e7018ced41e4
pros::delay(400);
intakeauton(127);  
chassis.waitUntilDone();

<<<<<<< HEAD
chassis.moveToPose(15, 58, 130, 4000, {.forwards = false, .lead = 0.3, .maxSpeed = 127, .minSpeed = 110,});
chassis.waitUntilDone();

}


void skills1() {

chassis.setPose(0, -58.5, 0);

intakeauton(127); 
conveyorauton(127);

//Get Middle Ring and Score on Alliance Stake
chassis.moveToPoint(0, -48, 3000, {.forwards = true, .maxSpeed = 127, .minSpeed = 110,}, true); //Async (moves on)
chassis.waitUntilDone();

while (!detectAndPauseIfRing()) {
    pros::delay(5); // check every 5ms
}

chassis.moveToPoint(0, -60, 3000, {.forwards = false, .maxSpeed = 127, .minSpeed = 110,});
chassis.waitUntilDone();

conveyorauton(127);
pros::delay(500);
conveyorauton(0);

hookauton(90); 
pros::delay(200);
hookauton(10);

//Get 1st mobile goal 
chassis.moveToPose(24, -40, -135, 3000, {.forwards = true,  .maxSpeed = 127, .minSpeed = 110});
chassis.waitUntilDone();

chassis.moveToPose(53, -19, -130, 3000, {.forwards = false,  .maxSpeed = 70, .minSpeed = 50});
chassis.waitUntilDone();

hookauton(-90);

//Get middle line of rings
chassis.moveToPose(48, 0, 0, 3000, {.forwards = true,  .maxSpeed = 127, .minSpeed = 110});
hookauton(-40);
chassis.waitUntilDone();

//Get 3 rings
chassis.moveToPose(48, -12, 0, 3000, {.forwards = false, .maxSpeed = 127, .minSpeed = 110});
chassis.waitUntilDone();

chassis.moveToPose(24, -24, -110, 3000, {.forwards = true, .maxSpeed = 127, .minSpeed = 110});
chassis.waitUntilDone();

chassis.moveToPose(4, -2, -45, 3000, {.forwards = true, .lead = 0.1, .maxSpeed = 127, .minSpeed = 110,});
chassis.waitUntilDone();

chassis.moveToPose(4, 3, -30, 3000, {.forwards = true, .lead = 0.05, .maxSpeed = 127, .minSpeed = 110,});
chassis.waitUntilDone(); 

//Get two rings and put mobile goal in corner
chassis.moveToPose(30, -25, -45, 3000, {.forwards = false, .lead = 0.1, .maxSpeed = 127, .minSpeed = 110,});
chassis.waitUntilDone();
chassis.moveToPose(48, -48, 135, 3000, {.forwards = true, .lead = 0.2, .maxSpeed = 127, .minSpeed = 110,});
chassis.waitUntilDone();
chassis.moveToPose(60, -56.5, 135, 3000, {.forwards = true, .maxSpeed = 90, .minSpeed = 70});
chassis.waitUntilDone();
chassis.moveToPose(48, -48, 135, 3000, {.forwards = false, .maxSpeed = 127, .minSpeed = 110,});
chassis.waitUntilDone();
chassis.turnToHeading(-45, 1000);
chassis.waitUntil(2);
chassis.moveToPose(56, -57, -45, 5000, {.forwards = false, .lead = 0.2, .maxSpeed = 127, .minSpeed = 110,});
pros::delay(300);
intakeauton(0); 
conveyorauton(0);
chassis.waitUntilDone();

hookauton(100);
pros::delay(300);
hookauton(10);

pros::delay(500);

//Drive to middle rings
chassis.moveToPose(60, 14, 0, 4000, {.forwards = true, .maxSpeed = 127, .minSpeed = 110,}, true);
intakeauton(127); 
conveyorauton(127);
chassis.waitUntilDone(); //async

while (!detectAndPauseIfRing()) {
    pros::delay(5); // check every 5ms
}

chassis.moveToPose(60, 0, 0, 3000, {.forwards = false, .maxSpeed = 127, .minSpeed = 110,});
chassis.waitUntilDone();

chassis.turnToHeading(90, 1000);
chassis.waitUntilDone();

// wallstake_lower_to_limit();

pros::delay(500);

wallstake_auton();

// wallstake_lower_to_limit();

//Go to 2nd mobile goal
chassis.moveToPose(24, 24, -45, 3000, {.forwards = true, .lead = 0.3, .maxSpeed = 127, .minSpeed = 110,});
chassis.waitUntilDone();




}

//Match Auton -----------------------------------------------------------------------------------------------------
void matchright() {

//chassis.follow(matchstart2_txt, 10, 4000, true);

=======
chassis.moveToPose(15, 58, 130, 4000, {.forwards = false, .lead = 0.3, .maxSpeed = 127});
chassis.waitUntilDone();
>>>>>>> 53fd74a816273b2edebe95cfef86e7018ced41e4
}