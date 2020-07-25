#include "main.h"

#include "class/control/chassis.h"
#include "class/control/auton.h"

Auton auton;

void autonomous() {
  printf("firstPos, secondPos, thirdPos %d %d %d \n", firstPos, secondPos, thirdPos);
  auton.run();
  }
