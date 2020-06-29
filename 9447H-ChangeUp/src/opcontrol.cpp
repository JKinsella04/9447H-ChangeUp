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
    intake.iiInit();
    slew.driveSlew(10); //7.5
    slew.intakeSlew(10);
  pros::delay(20);} //while
}
