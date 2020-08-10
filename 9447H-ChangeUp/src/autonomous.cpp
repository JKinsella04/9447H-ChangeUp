#include "main.h"

#include "class/control/chassis.h"
#include "class/control/auton.h"

Auton auton;

void autonomous() {
  printf("startPos, firstPos, secondPos, thirdPos %d %d %d %d \n", startPos, firstPos, secondPos, thirdPos);
  auton.run();
  }
