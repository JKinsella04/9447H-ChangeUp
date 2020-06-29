#include "main.h"

#include "class/control/chassis.h"
#include "class/control/auton.h"

void autonomous() {
  Auton auton;
  printf("firstPos, secondPos %d %d \n", firstPos, secondPos);
  auton.run();
  }
