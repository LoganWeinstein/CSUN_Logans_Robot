#include "autons.hpp"
#include "lemlib/chassis/chassis.hpp"
#include "main.h"
#include "lemlib/api.hpp"
#include "pros/rtos.hpp"
#include "subsystems.hpp"

#include "intake.hpp"
#include "wallstake.hpp"
#include "bullrush.hpp"
#include "hook.hpp"
#include "color.hpp"

/*
Notes
    - Have one robot touch the ladder for auton win point 
    - Make lower to limit a task so it runs independently 


*/

//Skills ---------------------------------------------------------
void skills_right() {

chassis.setPose(0, -58.5, 0);

intakeauton(127); 
conveyorauton(100);

//Get Middle Ring and Score on Alliance Stake
chassis.moveToPoint(0, -48, 3000, {.forwards = true, .maxSpeed = 70,}, true); //Async (moves on)
chassis.waitUntilDone();

wallstake_lower_to_limit();

while (!detectAndPauseIfRing()) {
    pros::delay(2); // check every 2ms
}

chassis.turnToHeading(180, 1000, {.maxSpeed = 110,});
chassis.waitUntilDone();

chassis.moveToPose(0, -55, 180, 3000, {.forwards = true, .maxSpeed = 127,}, true); //Async (moves on)
chassis.waitUntilDone();

wallstake_auton();

hookauton(30);
conveyorauton(127);

chassis.moveToPoint(0, -50, 3000, {.forwards = false, .maxSpeed = 100,}, true);
chassis.waitUntilDone();

//Get 1st mobile goal ------------------------

chassis.moveToPose(38, -30, -130, 2500, {.forwards = false, .lead = 0.2, .maxSpeed = 90,}); // Add last mintue slew
pros::delay(500);
wallstake_lower_to_limit();
chassis.waitUntilDone();

chassis.moveToPose(50, -20, -130, 1000, {.forwards = false, .maxSpeed = 50,});
chassis.waitUntilDone();

hookauton(-127);

pros::delay(100);

//Get middle line of rings ---------------------

chassis.moveToPose(48, 0, 0, 3000, {.forwards = true, .lead = 0.6, .maxSpeed = 127,});
hookauton(-60);
chassis.waitUntilDone();

chassis.moveToPose(48, -24, 0, 3000, {.forwards = false, .lead = 0.1, .maxSpeed = 127});
chassis.waitUntilDone();

chassis.moveToPose(24, -24, -90, 3000, {.forwards = true, .lead = 0.1, .maxSpeed = 127});
chassis.waitUntilDone();

chassis.turnToHeading(-45, 1000);
chassis.waitUntilDone();

chassis.moveToPose(6, -6, -45, 3000, {.forwards = true, .lead = 0.1, .maxSpeed = 127,}, true);
chassis.waitUntilDone();

while (!detectAndPauseIfRing()) {
    pros::delay(2); // check every 2ms
}

chassis.moveToPose(10, -10, -45, 3000, {.forwards = false, .lead = 0.1, .maxSpeed = 127,});
chassis.waitUntilDone(); 

chassis.moveToPose(6, 1, -30, 3000, {.forwards = true, .lead = 0.1, .maxSpeed = 127,});
pros::delay(900);
conveyorauton(127);
chassis.waitUntilDone(); 

pros::delay(300);

//Get two rings and put mobile goal in corner
chassis.moveToPose(24, -24, -45, 3000, {.forwards = false, .lead = 0.4, .maxSpeed = 127,});
conveyorauton(-127);
chassis.turnToHeading(135, 1000);
conveyorauton(127);
chassis.waitUntilDone();
chassis.moveToPose(61, -63, 135, 3000, {.forwards = true, .lead = 0.1, .maxSpeed = 80});
chassis.waitUntilDone();
chassis.moveToPose(48, -48, 135, 3000, {.forwards = false, .maxSpeed = 127,});
chassis.waitUntilDone();
chassis.turnToHeading(-45, 1000);
chassis.waitUntilDone();
chassis.moveToPose(61, -63, -45, 1500, {.forwards = false, .lead = 0.1, .maxSpeed = 127,});
pros::delay(300);
intakeauton(0); 
conveyorauton(0);
chassis.waitUntilDone();

conveyorauton(-90);
hookauton(100);
pros::delay(150);
hookauton(10);
conveyorauton(0);

pros::delay(500);

//Drive to middle rings and get load both (blue and red)
chassis.moveToPose(60, -10, 0, 3000, {.forwards = true, .maxSpeed = 127,});
intakeauton(127); 
conveyorauton(127);
chassis.waitUntilDone(); //async

chassis.moveToPose(60, 8, 0, 3000, {.forwards = false, .maxSpeed = 60,}, true);
chassis.waitUntilDone();

while (!detectAndPauseIfRing()) {
    pros::delay(5); // check every 5ms
}

chassis.moveToPose(62, 0, 0, 3000, {.forwards = false, .maxSpeed = 127,});
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

void skills_left() {


}

//RED Side ---------------------------------------------------------
void match_red_pos() {
//Initialize robot and reset everything
chassis.setPose(21, -50, 26);
static pros::Task detectionTask(objectDetectionTask, &Blue); // refine color sorting 


//Get right mobile goal  
chassis.moveToPose(45, -10, 26, 3000, {.forwards = true, .lead = 0.01, .maxSpeed = 127,});
chassis.waitUntil(20);
bullrushdown(); //Try switching to red motor for better hold?
chassis.waitUntil(28);
chassis.cancelMotion();

//Bring mobile goal back 
chassis.moveToPoint(21, -50, 1500, {.forwards = false, .maxSpeed = 127,});
chassis.waitUntil(25);
chassis.cancelMotion();

bullrushup();
hookauton(70); //Hook up 

chassis.moveToPose(34, -16, 225, 3000, {.forwards = false, .lead = 0.1, .maxSpeed = 60,}); 
chassis.waitUntilDone();

hookauton(-110); //Hook down
wallstake_lower_to_limit(); 
pros::delay(750);

//Get Two rings and corner rings (Color sensor on)
chassis.moveToPose(40, -24, 90, 3000, {.forwards = true, .maxSpeed = 90,}); 
pros::delay(600);
intakeauton(127);
conveyorauton(127);
hookauton(-40);
chassis.waitUntil(10);
chassis.cancelMotion();

chassis.moveToPose(53, -16, 45, 3000, {.forwards = true, .maxSpeed = 127,}); 
chassis.waitUntilDone();

chassis.moveToPose(62, -13, 50, 3000, {.forwards = true, .lead = 0.6, .maxSpeed = 127,}); 
chassis.waitUntilDone();

chassis.moveToPose(48, -24, 180, 1750, {.forwards = false, .maxSpeed = 127,});
chassis.waitUntilDone();

chassis.turnToHeading(180, 1000);
chassis.waitUntilDone();

chassis.moveToPose(46, -60, 185, 3000, {.forwards = true, .maxSpeed = 60,}); 
chassis.waitUntilDone();

chassis.moveToPose(48, -48, 180, 3000, {.forwards = false, .maxSpeed = 127,}); 
chassis.waitUntilDone();

intakeauton(-70);

//Go to corner
chassis.moveToPose(63, -62, 135, 2000, {.forwards = true, .maxSpeed = 127,});
chassis.waitUntilDone();

pros::delay(300);
intakeauton(127);
pros::delay(2000);

chassis.moveToPose(48, -48, 135, 3000, {.forwards = false, .maxSpeed = 127,}); 
chassis.waitUntilDone();

bullrushdown();

//Go to sweep corner position 
chassis.moveToPose(58, -57, 135, 2000, {.forwards = true, .maxSpeed = 127,});
chassis.waitUntilDone();

chassis.turnToHeading(300, 1000);
chassis.waitUntilDone();

chassis.turnToHeading(135, 1000);
bullrushup();
chassis.waitUntilDone();

chassis.turnToHeading(-45, 1000);
chassis.waitUntilDone();

chassis.moveToPose(59, -57, -45, 3000, {.forwards = false, .maxSpeed = 127,});
chassis.waitUntilDone();

hookauton(100);
conveyorauton(-100);
pros::delay(200);
hookauton(0);
conveyorauton(0);

wallstake_touch_ladder();

chassis.moveToPose(17, -17, -45, 2000, {.forwards = true, .maxSpeed = 127,});
intakeauton(0);
chassis.waitUntilDone();



}

void match_red_center() {
//Initialize robot and reset everything
chassis.setPose(21, -50, -30); //find correct starting angle
static pros::Task detectionTask(objectDetectionTask, &Blue);


//Get right mobile goal  
chassis.moveToPose(51, -10, 26, 3000, {.forwards = true, .maxSpeed = 127,});
chassis.waitUntil(25);
bullrushdown(); //Try switching to red motor for better hold?
chassis.waitUntil(33);
chassis.cancelMotion();

//Bring mobile goal back 
chassis.moveToPoint(21, -50, 1500, {.forwards = false, .maxSpeed = 127,});
chassis.waitUntil(25);
chassis.cancelMotion();

bullrushup();
hookauton(70); //Hook up 

chassis.moveToPose(34, -16, 225, 3000, {.forwards = false, .lead = 0.1, .maxSpeed = 60,}); 
chassis.waitUntilDone();

hookauton(-110); //Hook down
wallstake_lower_to_limit(); 
pros::delay(750);

//Get Two rings and corner rings (Color sensor on)
chassis.moveToPose(40, -24, 90, 3000, {.forwards = true, .maxSpeed = 90,}); 
pros::delay(600);
intakeauton(127);
conveyorauton(127);
hookauton(-40);
chassis.waitUntil(10);
chassis.cancelMotion();

chassis.moveToPose(53, -16, 45, 3000, {.forwards = true, .maxSpeed = 127,}); 
chassis.waitUntilDone();

chassis.moveToPose(62, -13, 50, 3000, {.forwards = true, .lead = 0.6, .maxSpeed = 127,}); 
chassis.waitUntilDone();

chassis.moveToPose(48, -24, 180, 1750, {.forwards = false, .maxSpeed = 127,});
chassis.waitUntilDone();

chassis.turnToHeading(180, 1000);
chassis.waitUntilDone();

chassis.moveToPose(46, -60, 185, 3000, {.forwards = true, .maxSpeed = 60,}); 
chassis.waitUntilDone();

chassis.moveToPose(48, -48, 180, 3000, {.forwards = false, .maxSpeed = 127,}); 
chassis.waitUntilDone();

intakeauton(-70);

//Go to corner
chassis.moveToPose(63, -62, 135, 2000, {.forwards = true, .maxSpeed = 127,});
chassis.waitUntilDone();

pros::delay(300);
intakeauton(127);
pros::delay(2000);

chassis.moveToPose(48, -48, 135, 3000, {.forwards = false, .maxSpeed = 127,}); 
chassis.waitUntilDone();

bullrushdown();

//Go to sweep corner position 
chassis.moveToPose(58, -57, 135, 2000, {.forwards = true, .maxSpeed = 127,});
chassis.waitUntilDone();

chassis.turnToHeading(300, 1000);
chassis.waitUntilDone();

chassis.turnToHeading(135, 1000);
bullrushup();
chassis.waitUntilDone();

chassis.turnToHeading(-45, 1000);
chassis.waitUntilDone();

chassis.moveToPose(59, -57, -45, 3000, {.forwards = false, .maxSpeed = 127,});
chassis.waitUntilDone();

hookauton(100);
conveyorauton(-100);
pros::delay(200);
hookauton(0);
conveyorauton(0);

wallstake_touch_ladder();

chassis.moveToPose(17, -17, -45, 2000, {.forwards = true, .maxSpeed = 127,});
intakeauton(0);
chassis.waitUntilDone();

}

void match_red_neg() {
//Initialize robot and reset everything
chassis.setPose(-21, -50, -26);
static pros::Task detectionTask(objectDetectionTask, &Blue);


//Get right mobile goal  
// chassis.moveToPoint(-51, -10, 3000, {.forwards = true, .maxSpeed = 127,});
chassis.moveToPose(-51, -10, -26, 3000, {.forwards = true, .maxSpeed = 127,});
chassis.waitUntil(25);
bullrushdown(); //Try switching to red motor for better hold?
chassis.waitUntil(32.7);
chassis.cancelMotion();

//Bring mobile goal back 
chassis.moveToPoint(-21, -50, 1500, {.forwards = false, .maxSpeed = 127,});
chassis.waitUntil(25);
chassis.cancelMotion();

bullrushup();
  
//Get open mobile goal and score alliance stake
chassis.moveToPoint(0, -48, 3000, {.forwards = false, .maxSpeed = 70,}); 
wallstake_lower_to_limit(); 
chassis.waitUntilDone();  

hookauton(-127);
wallstake_lower_to_limit(); 
pros::delay(500);

chassis.turnToHeading(180, 1000);
chassis.waitUntilDone();

intakeauton(127);
conveyorauton(127);

chassis.moveToPoint(0, -60, 3000, {.forwards = true, .maxSpeed = 90,}, true); //Async (moves on)
while (!detectAndPauseIfRing()) {
    pros::delay(2); // check every 2ms
}
chassis.waitUntilDone();

chassis.moveToPoint(0, -55, 3000, {.forwards = false, .maxSpeed = 127,}); 
chassis.waitUntilDone();

wallstake_auton();

wallstake_lower_to_limit(); 

chassis.moveToPose(-60, -48, -90, 3000, {.forwards = true, .lead = 0.1, .maxSpeed = 127,}); 
chassis.waitUntilDone();

chassis.moveToPose(-48, -48, -90, 3000, {.forwards = false, .lead = 0.1, .maxSpeed = 127,}); 
chassis.waitUntilDone();

chassis.turnToHeading(0, 1000);
chassis.waitUntilDone();

chassis.moveToPose(-48, -20, -90, 3000, {.forwards = true, .lead = 0.1, .maxSpeed = 127,}); 
chassis.waitUntilDone();

intakeauton(-70);

chassis.moveToPose(-63, -62, -135, 2000, {.forwards = true, .maxSpeed = 127,});
chassis.waitUntilDone();

pros::delay(300);
intakeauton(127);
pros::delay(2000);

chassis.moveToPose(-58, -57, -135, 2000, {.forwards = false, .maxSpeed = 127,});
chassis.waitUntilDone();

bullrushdown();

chassis.turnToHeading(-300, 1000);
chassis.waitUntilDone();

chassis.moveToPose(-50, -57, -180, 2000, {.forwards = true, .maxSpeed = 127,});
chassis.waitUntilDone();











}   

//BLUE Side ---------------------------------------------------------
void match_blue_pos() {
//Initialize robot and reset everything
chassis.setPose(-21, -50, -26);
static pros::Task detectionTask(objectDetectionTask, &Red);


//Get right mobile goal  
chassis.moveToPose(-51, -10, -26, 3000, {.forwards = true, .maxSpeed = 127,});
chassis.waitUntil(25);
bullrushdown(); //Try switching to red motor for better hold?
chassis.waitUntil(33);
chassis.cancelMotion();

//Bring mobile goal back 
chassis.moveToPoint(-21, -50, 1500, {.forwards = false, .maxSpeed = 127,});
chassis.waitUntil(25);
chassis.cancelMotion();

bullrushup();
hookauton(70); //Hook up 

chassis.moveToPose(-34, -16, 225, 3000, {.forwards = false, .lead = 0.1, .maxSpeed = 60,}); 
chassis.waitUntilDone();

hookauton(-110); //Hook down
wallstake_lower_to_limit(); 
pros::delay(750);

//Get Two rings and corner rings (Color sensor on)
chassis.moveToPose(-40, -24, -90, 3000, {.forwards = true, .maxSpeed = 90,}); 
pros::delay(600);
intakeauton(127);
conveyorauton(127);
hookauton(-40);
chassis.waitUntil(10);
chassis.cancelMotion();

chassis.moveToPose(-53, -16, -45, 3000, {.forwards = true, .maxSpeed = 127,}); 
chassis.waitUntilDone();

chassis.moveToPose(-62, -13, -50, 3000, {.forwards = true, .lead = 0.6, .maxSpeed = 127,}); 
chassis.waitUntilDone();

chassis.moveToPose(-48, -24, 180, 1750, {.forwards = false, .maxSpeed = 127,});
chassis.waitUntilDone();

chassis.turnToHeading(180, 1000);
chassis.waitUntilDone();

chassis.moveToPose(-46, -60, -185, 3000, {.forwards = true, .maxSpeed = 60,}); 
chassis.waitUntilDone();

chassis.moveToPose(-48, -48, 180, 3000, {.forwards = false, .maxSpeed = 127,}); 
chassis.waitUntilDone();

intakeauton(-70);

chassis.moveToPose(-63, -62, -135, 2000, {.forwards = true, .maxSpeed = 127,});
chassis.waitUntilDone();

pros::delay(300);
intakeauton(127);
pros::delay(1500);

chassis.moveToPose(-48, -48, -135, 3000, {.forwards = false, .maxSpeed = 127,}); 
chassis.waitUntilDone();

bullrushdown();

chassis.moveToPose(-58, -57, -135, 2000, {.forwards = true, .maxSpeed = 127,});
chassis.waitUntilDone();

chassis.turnToHeading(-255, 1000);
chassis.waitUntilDone();

chassis.turnToHeading(-135, 1000);
bullrushup();
chassis.waitUntilDone();

chassis.turnToHeading(45, 1000);
chassis.waitUntilDone();

chassis.moveToPose(-59, -57, 45, 3000, {.forwards = false, .maxSpeed = 127,});
chassis.waitUntilDone();

hookauton(100);
conveyorauton(-100);
pros::delay(200);
hookauton(0);
conveyorauton(0);

wallstake_touch_ladder();

chassis.moveToPose(-17, -17, 45, 2000, {.forwards = true, .maxSpeed = 127,});
chassis.waitUntilDone();










}  

void match_blue_center() {

}

void match_blue_neg() {
//Initialize robot and reset everything
chassis.setPose(21, -50, 26);
static pros::Task detectionTask(objectDetectionTask, &Red);


//Get right mobile goal  
chassis.moveToPose(51, -10, 26, 3000, {.forwards = true, .maxSpeed = 127,});
chassis.waitUntil(25);
bullrushdown(); //Try switching to red motor for better hold?
chassis.waitUntil(33);
chassis.cancelMotion();

//Bring mobile goal back 
chassis.moveToPoint(21, -50, 1500, {.forwards = false, .maxSpeed = 127,});
chassis.waitUntil(25);
chassis.cancelMotion();

bullrushup();
hookauton(70); //Hook up 

chassis.moveToPose(34, -16, 225, 3000, {.forwards = false, .lead = 0.1, .maxSpeed = 60,}); 
chassis.waitUntilDone();

hookauton(-110); //Hook down
wallstake_lower_to_limit(); 
pros::delay(750);
  
//Get open mobile goal and score alliance stake
chassis.moveToPoint(0, -48, 3000, {.forwards = false, .maxSpeed = 60,}); 
chassis.waitUntilDone();  

hookauton(-127);
wallstake_lower_to_limit(); 
pros::delay(500);

chassis.turnToHeading(180, 1000);
chassis.waitUntilDone();

intakeauton(127);
conveyorauton(127);

while (!detectAndPauseIfRing()) {
    pros::delay(2); // check every 2ms
}

chassis.moveToPoint(0, -60, 3000, {.forwards = true, .maxSpeed = 90,}, true); //Async (moves on)
chassis.waitUntilDone();

chassis.moveToPoint(0, -55, 3000, {.forwards = false, .maxSpeed = 127,}); 
chassis.waitUntilDone();

wallstake_auton();

wallstake_lower_to_limit(); 





}    
    
    
    
    
    
    