#include "main.h"

//Controller Definition
pros::Controller master(CONTROLLER_MASTER);

//Motor Definitions

//Intakes
pros::Motor leftIntake(15, MOTOR_GEARSET_18, 0, MOTOR_ENCODER_ROTATIONS); //1
pros::Motor middleIntake(1, MOTOR_GEARSET_18, 0, MOTOR_ENCODER_ROTATIONS); //1
pros::Motor rightIntake(14, MOTOR_GEARSET_18, 1, MOTOR_ENCODER_ROTATIONS); //16

//Indexer Motors
pros::Motor indexer(20, MOTOR_GEARSET_18, 0, MOTOR_ENCODER_ROTATIONS); //1

//Drive Base
pros::Motor LF(16, MOTOR_GEARSET_18, 0, MOTOR_ENCODER_COUNTS), //19,9,13,
            LB(10, MOTOR_GEARSET_18, 0, MOTOR_ENCODER_COUNTS),
            RF(3, MOTOR_GEARSET_18, 0, MOTOR_ENCODER_COUNTS),
            RB(7, MOTOR_GEARSET_18, 0, MOTOR_ENCODER_COUNTS);

//Sensor Definitions
pros::Vision vis(13);

pros::Imu M_IMU(6), L_IMU(9), R_IMU(5);

//Motor Encoders
pros::ADIEncoder LEncoder('H', 'G'),
                 REncoder('B', 'A', true);
                 // MEncoder(4, 5); //3,4

pros::ADIAnalogIn botLight('C');
pros::ADIAnalogIn topLight('F');

//Global Variables
int currentPos = 0,
    startPos = 0,
    firstPos = 0,
    secondPos = 0,
    thirdPos = 0,
    alliance = 0;

bool *isSetup = new bool[false];
