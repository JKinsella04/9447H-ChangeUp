#include "main.h"
#include "globals.hpp"

#include "class/control/intakes.hpp"
#include "class/control/slew.hpp"

// Class Initialization
static Slew slew;
static Intake intake;


void opcontrol() {
  while (true) {
    slew.tankDrive(1000, 500, 900);
    intake.runIntakes();
    pros::delay(15);
  }
}
