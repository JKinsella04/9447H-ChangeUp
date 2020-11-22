#include "main.h"

//Controller Definition
pros::Controller master(CONTROLLER_MASTER);

//Motor Definitions

//Intakes
pros::Motor leftIntake(15, MOTOR_GEARSET_18, 0, MOTOR_ENCODER_ROTATIONS); //1
pros::Motor middleIntake(1, MOTOR_GEARSET_6, 0, MOTOR_ENCODER_ROTATIONS); //1
pros::Motor rightIntake(14, MOTOR_GEARSET_18, 1, MOTOR_ENCODER_ROTATIONS); //16

//Indexer Motors
pros::Motor indexer(20, MOTOR_GEARSET_18, 0, MOTOR_ENCODER_ROTATIONS); //1

//Drive Base
pros::Motor LF(16, MOTOR_GEARSET_18, 0, MOTOR_ENCODER_COUNTS), //19,9,13,
            LB(10, MOTOR_GEARSET_18, 0, MOTOR_ENCODER_COUNTS),
            RF(3, MOTOR_GEARSET_18, 0, MOTOR_ENCODER_COUNTS),
            RB(7, MOTOR_GEARSET_18, 0, MOTOR_ENCODER_COUNTS);

/*
Optical Sensors
ROptical Optical Sensor on the right of the robot.
LOptical Optical Sensor on the left of the robot.
*/
pros::Optical ROptical(2), LOptical(12);

/*
Inertial sensor
L_IMU  Left facing inertial sensor.
M_IMU  Front facing inertial sensor.
R_IMU  Right facing inertial sensor.
*/
pros::Imu M_IMU(6), L_IMU(9), R_IMU(5);

//Free Spinning Wheel Encoders
pros::ADIEncoder LEncoder('G', 'H'),
                 REncoder('B', 'A', false);
//Line Sensors
pros::ADIAnalogIn botLight('C');
pros::ADIAnalogIn topLight('F');

/*
 Global Variables + Pointers

 @param currentPos how the robot keeps track of what position it is at during autonomous.
 @param startPos the beginning spot for the robot during autonomous.
 @param firstPos first place for the robot to go to during autonomous.
 @param secondPos second place for the robot to go to during autonomous.
 @param thirdPos third place for the robot to go to during autonomous.
 @param alliance Determines what color to sort for when running the autoSort intake class member function.
*/
int currentPos = 0,
    startPos = 0,
    firstPos = 0,
    secondPos = 0,
    thirdPos = 0,
    alliance = 0;

bool *isSetup = new bool[false];
