#include "main.h"
#include "class/control/chassis.h"
#include "class/displayController.h"

Display display;

void initialize() {
  display.setup();
if(isSetup){display.destroy();}
}

void competition_initialize() {
    display.display();
  while(1){
  display.backgroundcheck();
  while(alliance==0){display.setAlliance(); pros::delay(15);}
  display.arcChecker();
  display.setVars();
  display.updateSensors();
  pros::delay(20);}
}
