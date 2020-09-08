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
    slew.driveSlew(1000, 200, 800); //7.5
    // intake.runIntakes();
    // slew.allSlew(1, 50);
    // pros::ADIAnalogIn sensor('C');
    double sensorvalue = sensor.get_value();
    if(sensor.get_value() <= 2200)intake.middleStop();
  pros::delay(20);
} //while


}
