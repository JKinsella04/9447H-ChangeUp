#include "main.h"
#include "class/control/chassis.h"
#include "class/displayController.h"

void initialize() {

  // pros::delay(20);
}


void competition_initialize() {
  Chassis chassis;
  Display display;

  chassis.reset();
  display.display();
  while(1){
  display.backgroundcheck();
  // display.arcchecker();
  display.loadAuton();
  pros::delay(20);
}
}
