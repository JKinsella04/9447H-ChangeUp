#include "main.h"
#include "globals.h"


#include "class/control/chassis.h"
#include "class/control/intakes.h"
#include "class/control/arm.h"
#include "class/displayController.h"
#include "class/control/slew.h"

// Class Initialization
 Chassis chassis;
 Slew slew;

void opcontrol() {
  LEncoder.reset();
  MEncoder.reset();
  REncoder.reset();

  while (true) {
    slew.driveSlew(5);

    // LF.move_velocity(master.get_analog(ANALOG_LEFT_Y) * 1.6 + master.get_analog(ANALOG_LEFT_X) * 1.6 + master.get_analog(ANALOG_RIGHT_X) * 1.6);
    // LB.move_velocity(master.get_analog(ANALOG_LEFT_Y) * 1.6 - master.get_analog(ANALOG_LEFT_X) * 1.6 + master.get_analog(ANALOG_RIGHT_X) * 1.6);
    // RF.move_velocity(-master.get_analog(ANALOG_LEFT_Y) * 1.58 + master.get_analog(ANALOG_LEFT_X) * 1.58 + master.get_analog(ANALOG_RIGHT_X) * 1.58);
    // RB.move_velocity(-master.get_analog(ANALOG_LEFT_Y) * 1.58 - master.get_analog(ANALOG_LEFT_X) * 1.58 + master.get_analog(ANALOG_RIGHT_X) * 1.58);

    std::cout << LEncoder.get_value()<< "," << MEncoder.get_value() << ", "<< REncoder.get_value() << std::endl;
    }
  }
