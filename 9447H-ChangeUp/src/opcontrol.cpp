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
    // double leftJoystick = master.get_analog(ANALOG_LEFT_Y);
    // double rightJoystick = master.get_analog(ANALOG_RIGHT_Y);
    // double bothJoystick = leftJoystick/rightJoystick;
    // double leftError = leftJoystick*1.58 - 0;
    // printf("left, right, both, leftError  %F %F %F %F \n", leftJoystick, rightJoystick, bothJoystick, leftError);
    slew.driveSlew(5); //7.5
    // slew.intakeSlew(100);
    // slew.indexerSlew(100);
    slew.allSlew();
  pros::delay(20);} //while
}
