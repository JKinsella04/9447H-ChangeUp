#include "main.h"
#include "globals.hpp"

#include "class/control/intakes.hpp"
#include "class/control/slew.hpp"

// Class Initialization
static Slew slew;
static Intake intake;


void opcontrol() {
  while (true) {
    printf("Left, Right: %d %d\n", LEncoder.get_value(), REncoder.get_value());

    slew.tankDrive(1000, 500, 900);
    intake.runIntakes();
    pros::delay(15);
  }
}
