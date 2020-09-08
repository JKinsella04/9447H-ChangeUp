#include "main.h"

//Controller Definition
pros::Controller master(CONTROLLER_MASTER);

//Motor Definitions

//Intakes
pros::Motor leftIntake(19, MOTOR_GEARSET_18, 0, MOTOR_ENCODER_ROTATIONS); //1
pros::Motor middleIntake(10, MOTOR_GEARSET_18, 1, MOTOR_ENCODER_ROTATIONS); //1
pros::Motor rightIntake(17, MOTOR_GEARSET_18, 1, MOTOR_ENCODER_ROTATIONS); //16

//Indexer Motors
pros::Motor indexer(2, MOTOR_GEARSET_18, 0, MOTOR_ENCODER_ROTATIONS); //1

//Drive Base
pros::Motor LF(19, MOTOR_GEARSET_18, 0, MOTOR_ENCODER_COUNTS), //19,9,13,
            LB(10, MOTOR_GEARSET_18, 0, MOTOR_ENCODER_COUNTS),
            RF(17, MOTOR_GEARSET_18, 0, MOTOR_ENCODER_COUNTS),
            RB(2, MOTOR_GEARSET_18, 0, MOTOR_ENCODER_COUNTS);

//Sensor Definitions
pros::Vision vis(15);

pros::Imu M_IMU(7), L_IMU(4), R_IMU(8);

//Motor Encoders
pros::ADIEncoder LEncoder(7, 8),
                 REncoder(1, 2, true),
                 MEncoder(4, 5); //3,4

pros::ADIAnalogIn sensor('C');

//Global Variables
int currentPos = 0,
    startPos = 0,
    firstPos = 0,
    secondPos = 0,
    thirdPos = 0,
    alliance = 0;

bool *isSetup = new bool[false];
