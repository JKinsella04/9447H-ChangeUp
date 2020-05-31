#include "main.h"
//Controller Definition
pros::Controller master(CONTROLLER_MASTER);

//Motor Definitions

//Intakes
pros::Motor leftIntake(12, MOTOR_GEARSET_18, 0, MOTOR_ENCODER_ROTATIONS);
pros::Motor rightIntake(11, MOTOR_GEARSET_18, 1, MOTOR_ENCODER_ROTATIONS);
//Drive Base
pros::Motor LF(19, MOTOR_GEARSET_18, 0, MOTOR_ENCODER_COUNTS), //19,9,13,
            LB(10, MOTOR_GEARSET_18, 0, MOTOR_ENCODER_COUNTS),
            RF(17, MOTOR_GEARSET_18, 0, MOTOR_ENCODER_COUNTS),
            RB(2, MOTOR_GEARSET_18, 0, MOTOR_ENCODER_COUNTS);
//Arm Motors
pros::Motor leftArm(1, MOTOR_GEARSET_18, 0, MOTOR_ENCODER_ROTATIONS);
pros::Motor rightArm(1, MOTOR_GEARSET_18, 1, MOTOR_ENCODER_ROTATIONS);

//Sensor Definitions

//Inertial Sensors
pros::Imu M_IMU(7), L_IMU(4), R_IMU(8);

//Motor Encoders
pros::ADIEncoder LEncoder(7, 8),
                 REncoder(1, 2, true),
                 MEncoder(3, 4);
