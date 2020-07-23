#include "main.h"

#include "class/control/chassis.h"
#include "class/control/auton.h"

void autonomous() {
  Auton auton;
  Chassis chassis;
  printf("firstPos, secondPos, thirdPos %d %d %d \n", firstPos, secondPos, thirdPos);
  auton.run();
  // chassis.withPD(0.075,0.001).withSlew(2).drive(3500);
  }
