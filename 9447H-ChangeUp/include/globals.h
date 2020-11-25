#include "main.h"
//Controller Definition
extern pros::Controller master;

//Motor Declarations
extern pros::Motor leftIntake;
extern pros::Motor middleIntake;
extern pros::Motor rightIntake;
extern pros::Motor LF, LB, RF, RB;
extern pros::Motor indexer;


//Sensor Declarations
extern pros::Optical ROptical, LOptical;

extern pros::Imu M_IMU, L_IMU, R_IMU;

//Motor Encoders
extern pros::ADIEncoder LEncoder, REncoder;
extern pros::ADIAnalogIn topLight;

//Global Variables
extern int currentPos, startPos, firstPos, secondPos, thirdPos, alliance;
extern bool *isSetup;
