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
  LF.set_brake_mode(MOTOR_BRAKE_HOLD);
  LB.set_brake_mode(MOTOR_BRAKE_HOLD);
  RF.set_brake_mode(MOTOR_BRAKE_HOLD);
  RB.set_brake_mode(MOTOR_BRAKE_HOLD);
  intake.iiInit();
  while (true) {
    slew.driveSlew(1000, 900, 900);
    intake.runIntakes();
    pros::delay(15);
  }
}
