#include "main.h"
#include "globals.h"

#include "class/control/intakes.hpp"
#include "class/control/slew.hpp"

// Class Initialization
Slew slew;
Intake intake;


void opcontrol() {
  LF.set_brake_mode(MOTOR_BRAKE_HOLD);
  LB.set_brake_mode(MOTOR_BRAKE_HOLD);
  RF.set_brake_mode(MOTOR_BRAKE_HOLD);
  RB.set_brake_mode(MOTOR_BRAKE_HOLD);
  intake.iiInit();
  while (true) {
    slew.tankDrive(1000, 900, 900);
    // slew.arcadeControl(1000, 900, 900);
    intake.runIntakes();
    pros::delay(15);
  }
}
