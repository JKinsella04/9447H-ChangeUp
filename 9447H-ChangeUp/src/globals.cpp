#include "main.h"
//Controller Definition
pros::Controller master(CONTROLLER_MASTER);

//Motor Definitions

//Intakes
pros::Motor leftIntake(1, MOTOR_GEARSET_18, 0, MOTOR_ENCODER_ROTATIONS); //12
pros::Motor middleIntake(1, MOTOR_GEARSET_18, 1, MOTOR_ENCODER_ROTATIONS);
pros::Motor rightIntake(16, MOTOR_GEARSET_18, 1, MOTOR_ENCODER_ROTATIONS); //16

//Indexer Motors
pros::Motor indexer(1, MOTOR_GEARSET_18, 0, MOTOR_ENCODER_ROTATIONS);

//Drive Base
pros::Motor LF(19, MOTOR_GEARSET_18, 0, MOTOR_ENCODER_COUNTS), //19,9,13,
            LB(10, MOTOR_GEARSET_18, 0, MOTOR_ENCODER_COUNTS),
            RF(17, MOTOR_GEARSET_18, 0, MOTOR_ENCODER_COUNTS),
            RB(2, MOTOR_GEARSET_18, 0, MOTOR_ENCODER_COUNTS);

//Sensor Definitions
pros::Vision vis(13);

pros::Imu M_IMU(7), L_IMU(4), R_IMU(8);

//Motor Encoders
pros::ADIEncoder LEncoder(7, 8),
                 REncoder(1, 2, true),
                 MEncoder(3, 4);

//Global Variables
int currentPos = 0,
    startPos = 0,
    firstPos = 0,
    secondPos = 0,
    thirdPos = 0;

bool *isSetup = new bool[false];
