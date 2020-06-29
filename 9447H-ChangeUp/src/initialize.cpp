#include "main.h"
#include "class/control/chassis.h"
#include "class/displayController.h"

Display display;

void initialize() {}

void competition_initialize() {
  display.sensorReset();
  display.display();
  while(1){
  display.backgroundcheck();
  display.arcchecker();
  while(firstPos == 0){ display.setFirst(); pros::delay(20);}
  pros::delay(250);
  while(secondPos == 0 && firstPos != 0){ display.setSecond(); pros::delay(20);}
  pros::delay(20);}
}
