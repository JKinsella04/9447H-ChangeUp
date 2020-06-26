#include "main.h"
#include "globals.h"

#include "class/control/chassis.h"
#include "class/control/intakes.h"
#include "class/displayController.h"
#include "class/control/slew.h"

// Class Initialization
 Chassis chassis;
 Slew slew;

void opcontrol() {
  while (true) {
    slew.driveSlew(10); //7.5
    
  } //while
}
