#include "main.h"
#include "globals.h"

#include "class/control/chassis.h"
#include "class/control/intakes.h"
#include "class/displayController.h"
#include "class/control/slew.h"

// Class Initialization
// Chassis chassis;
Slew slew;
Intake intake;


void opcontrol() {
  while (true) {
    LF.set_brake_mode(MOTOR_BRAKE_HOLD);
    LB.set_brake_mode(MOTOR_BRAKE_HOLD);
    RF.set_brake_mode(MOTOR_BRAKE_HOLD);
    RB.set_brake_mode(MOTOR_BRAKE_HOLD);
    intake.iiInit();
    // intake.autoSort();
    slew.driveSlew(900, 720, 720); //7.5
    intake.runIntakes();
    intake.runAutoIndexer();
    // slew.allSlew(1, 50);
    // pros::ADIAnalogIn sensor('C');
  pros::delay(20);
} //while


}
