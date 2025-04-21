#include "main.h"
#include "lemlib/api.hpp" // IWYU pragma: keep
#include "lemlib/chassis/chassis.hpp"
#include "lemlib/chassis/trackingWheel.hpp"
#include "subsystems.hpp"
#include "intake.hpp"
#include "wallstake.hpp"
#include "bullrush.hpp"
#include "hook.hpp"
#include "color.hpp"



// controller
pros::Controller controller(pros::E_CONTROLLER_MASTER);

// motor groups
pros::MotorGroup leftMotors({-1, 2, -3},
                            pros::MotorGearset::blue); // left motor group - ports 3 (reversed), 4, 5 (reversed)
pros::MotorGroup rightMotors({4, -5, 6}, pros::MotorGearset::blue); // right motor group - ports 6, 7, 9 (reversed)

// Inertial Sensor on port 21
pros::Imu imu(21);

// tracking wheels
// horizontal tracking wheel encoder. Rotation sensor, port 20, not reversed
pros::Rotation horizontalEnc(17);
// vertical tracking wheel encoder. Rotation sensor, port 11, reversed 
pros::Rotation verticalEncLeft(15);
pros::Rotation verticalEncRight(16);

// horizontal tracking wheel. 2.75" diameter, 5.75" offset, back of the robot (negative)
lemlib::TrackingWheel horizontal(&horizontalEnc, lemlib::Omniwheel::OLD_275, -3.430, 1);

// vertical tracking wheel. 2.75" diameter, 2.5" offset, left of the robot (negative)
lemlib::TrackingWheel verticalLeft(&verticalEncLeft, lemlib::Omniwheel::NEW_275_HALF, -4.0, 1);   
// lemlib::TrackingWheel verticalRight(&verticalEncRight, lemlib::Omniwheel::NEW_4, 5.975, 1.56); 
// lemlib::TrackingWheel verticalLeft(&verticalEncLeft, lemlib::Omniwheel::NEW_4, -5.975, 1.56);

// drivetrain settings
lemlib::Drivetrain drivetrain(&leftMotors, // left motor group
                              &rightMotors, // right motor group
                              12, // 10 inch track width
                              lemlib::Omniwheel::NEW_4, // using new 4" omnis
                              360, // drivetrain rpm is 360
                              12 // horizontal drift is 2. If we had traction wheels, it would have been 8
);

// lateral motion controller
lemlib::ControllerSettings linearController(10, // proportional gain (kP)
                                            0, // integral gain (kI)
                                            3, // derivative gain (kD)
                                            3, // anti windup
                                            2, // Original: 1  small error range, in inches  
                                            250, // Original: 100  small error range timeout, in milliseconds
                                            4, // Original: 3  large error range, in inches
                                            400, // Original: 200  large error range timeout, in milliseconds
                                            20 // maximum acceleration (slew)
);

// angular motion controller
lemlib::ControllerSettings angularController(2, // proportional gain (kP)
                                             0, // integral gain (kI)
                                             10, // derivative gain (kD)
                                             3, // anti windup
                                             1, // small error range, in degrees
                                             100, // small error range timeout, in milliseconds
                                             3, // large error range, in degrees
                                             500, // large error range timeout, in milliseconds
                                             0 // maximum acceleration (slew)
);

// sensors for odometry
lemlib::OdomSensors sensors(&verticalLeft, // vertical tracking wheel
                            nullptr, // vertical tracking wheel 2, set to nullptr as we don't have a second one
                            &horizontal, // horizontal tracking wheel
                            nullptr, // horizontal tracking wheel 2, set to nullptr as we don't have a second one
                            &imu // inertial sensor
);

// input curve for throttle input during driver control
lemlib::ExpoDriveCurve throttleCurve(5, // joystick deadband out of 127
                                     12, // minimum output where drivetrain will move out of 127
                                     1.01 // expo curve gain
);

//original joystick values: (3, 10, 1.019)

// input curve for steer input during driver control
lemlib::ExpoDriveCurve steerCurve(18, // joystick deadband out of 127
                                  12, // minimum output where drivetrain will move out of 127
                                  1.03 // expo curve gain
);

// create the chassis
lemlib::Chassis chassis(drivetrain, linearController, angularController, sensors, &throttleCurve, &steerCurve);

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
    chassis.calibrate(); // calibrate sensors
    pros::lcd::initialize(); // initialize brain screen
   

    // the default rate is 50. however, if you need to change the rate, you
    // can do the following.
    // lemlib::bufferedStdout().setRate(...);
    // If you use bluetooth or a wired connection, you will want to have a rate of 10ms

    // for more information on how the formatting for the loggers
    // works, refer to the fmtlib docs

    // thread to for brain screen and position logging -------------------------------------

    // pros::Task screenTask([&]() {
    //     while (true) {
    //         // print robot location to the brain screen
    //         pros::lcd::print(0, "X: %f", chassis.getPose().x); // x
    //         pros::lcd::print(1, "Y: %f", chassis.getPose().y); // y
    //         pros::lcd::print(2, "Theta: %f", chassis.getPose().theta); // heading
    //         // log position telemetry
    //         lemlib::telemetrySink()->info("Chassis pose: {}", chassis.getPose());
    //         // delay to save resources
    //         pros::delay(50);
    //     }
    // });
}

/**
 * Runs while the robot is disabled
 */
void disabled() {}

/**
 * runs after initialize if the robot is connected to field control
 */
void competition_initialize() {}

// get a path used for pure pursuit
// this needs to be put outside a function
// '.' replaced with "_" to make c++ happy
// ASSET(matchstart2_txt);
// ASSET();
// ASSET();
/**
 * Runs during auto
 *
 * This is an example autonomous routine which demonstrates a lot of the features LemLib has to offer
 */

//**NO MINIMUM SPEED, doesent allow robot to decelerate to correct heading/position 

 void skillsright() {
chassis.setPose(24, -55.5, 180);

hookauton(110); 
pros::delay(200);
hookauton(0);

//Get mobile goal 
chassis.moveToPose(56, -12, -130, 4000, {.forwards = false,  .maxSpeed = 70, .minSpeed = 50});
chassis.waitUntilDone();

hookauton(-127);
intakeauton(127); 
conveyorauton(127);  

pros::delay(200);

chassis.moveToPose(48, -45, 180, 4000, {.forwards = true, .maxSpeed = 127, .minSpeed = 110});
chassis.waitUntilDone();

hookauton(-50);

//Get corner
chassis.moveToPose(60, -56.5, 135, 3000, {.forwards = true, .lead = 0.55, .maxSpeed = 90, .minSpeed = 70});
chassis.waitUntilDone();

pros::delay(1000);

chassis.moveToPose(48, -48, 135, 4000, {.forwards = false, .maxSpeed = 127, .minSpeed = 110,});
chassis.waitUntilDone();

chassis.turnToHeading(-90, 2000, {.direction = AngularDirection::CW_CLOCKWISE, .maxSpeed = 127, .minSpeed = 110,});
chassis.waitUntilDone();

//Get middle ring and score on aliance stake
chassis.moveToPose(-8, -48, -90, 5000, {.forwards = true, .maxSpeed = 127, .minSpeed = 110,});
while (!detectAndPauseIfRing()) {
    pros::delay(5); // check every 10ms
}
chassis.waitUntilDone();

// wallstake_lower_to_limit();

chassis.moveToPose(0, -48, -90, 4000, { .forwards = false, .lead = 0.1, .maxSpeed = 127, .minSpeed = 110});
chassis.waitUntilDone();
chassis.turnToHeading(180, 2000, {.direction = AngularDirection::CCW_COUNTERCLOCKWISE, .maxSpeed = 127, .minSpeed = 110});
chassis.waitUntil(2);
chassis.moveToPoint(0, -55, 4000, { .forwards = true, .maxSpeed = 50, .minSpeed = 30,});
chassis.waitUntilDone();

wallstake_auton();

// wallstake_lower_to_limit();

conveyorauton(127);

//Get Center Ring
chassis.moveToPose(24, -24, 0, 3000, {.forwards = true, .lead = 0.5, .maxSpeed = 127, .minSpeed = 30,});
chassis.waitUntilDone();
chassis.moveToPose(4, -2, -45, 3000, {.forwards = true, .lead = 0.1, .maxSpeed = 127, .minSpeed = 110,});
chassis.waitUntilDone();

pros::delay(500);
conveyorauton(-90);

chassis.moveToPose(24, -24, -45, 3000, {.forwards = false, .maxSpeed = 127, .minSpeed = 110,});
chassis.waitUntilDone();

conveyorauton(127);

//Get middle line rings
chassis.moveToPose(45, 0, 90, 3000, {.forwards = true, .lead = 0.05, .maxSpeed = 70, .minSpeed = 50,});
chassis.waitUntilDone();
chassis.moveToPose(63, 3, 80, 3000, {.forwards = true, .lead = 0.05, .maxSpeed = 70, .minSpeed = 50,});
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

//Drive to 2nd Mobile Goal make forward to back transition 
chassis.moveToPose(40, 0, 0, 4000, {.forwards = true, .lead = 0.2, .maxSpeed = 127, .minSpeed = 110,});
hookauton(50);
chassis.waitUntilDone();
chassis.moveToPose(13, 30, -45, 5000, {.forwards = false, .lead = 0.2, .maxSpeed = 60, .minSpeed = 30,});
chassis.waitUntil(2);

pros::delay(800);
hookauton(-110);
pros::delay(300);

intakeauton(127);  
conveyorauton(127);

//Get Center Ring first 
chassis.moveToPose(0, 0, -135, 4000, {.forwards = true, .lead = 0.3, .maxSpeed = 127, .minSpeed = 110,});
chassis.waitUntilDone();

hookauton(-60);

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

void autonomous() {
    // eye.set_led_pwm(100);
    // pros::Task detectTask(objectDetectionTask);
    
    // // Enable color detection right from the start
    // setColorDetectionEnabled(true);

//Call Different Autons from above
skillsRnew();
// skillsright();


}

//Match Auton (right side)///////////////////////////////////////

// chassis.follow(matchstart2_txt, 10, 4000, true);




// // Move to x: 0 and y: 0 and face heading 270, going backwards. Timeout set to 4000ms
// chassis.moveToPose(0, 0, 270, 4000, {.forwards = false});
// // cancel the movement after it has traveled 10 inches
// chassis.waitUntil(10);
// chassis.cancelMotion();
// // Turn to face the point x:45, y:-45. Timeout set to 1000
// // dont turn faster than 60 (out of a maximum of 127)
// chassis.turnToPoint(45, -45, 1000, {.maxSpeed = 60});
// // Turn to face a direction of 90º. Timeout set to 1000
// // will always be faster than 100 (out of a maximum of 127)
// // also force it to turn clockwise, the long way around
// chassis.turnToHeading(90, 1000, {.direction = AngularDirection::CW_CLOCKWISE, .minSpeed = 100});
// // Follow the path in path.txt. Lookahead at 15, Timeout set to 4000
// // following the path with the back of the robot (forwards = false)
// // see line 116 to see how to define a path
// chassis.follow(example_txt, 15, 4000, false);
// // wait until the chassis has traveled 10 inches. Otherwise the code directly after
// // the movement will run immediately
// // Unless its another movement, in which case it will wait
// chassis.waitUntil(10);
// pros::lcd::print(4, "Traveled 10 inches during pure pursuit!");
// // wait until the movement is done
// chassis.waitUntilDone();
// pros::lcd::print(4, "pure pursuit finished!");


/**
 * Runs in driver control
 */
void opcontrol() {
	
pros::lcd::initialize();
   
    
pros::Task wallstake_task(wallstakecontrol);
pros::Task bullrush_task(bullrushcontrol);
   
// bool wasPressed = false;

while (true) {
    // double angle = wallstake_sensor.get_position();
    // double corrected = angle / 100;
    // pros::lcd::print(0, "Wallstake Angle:");
    // pros::lcd::print(1, "%.2f deg", corrected);

    // bool pressed = !limitswitch.get_value();
    //     if (pressed && !wasPressed) {
    //         wallstake_sensor.reset_position();
    //         pros::lcd::print(2, "Limit Hit -> Reset");
    //     }
    //     wasPressed = pressed;


        int leftY = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
        int rightY = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y);
        chassis.tank(leftY, rightY);

        intakecontrol();
        hookcontrol();
        
        pros::delay(25);
    }
}