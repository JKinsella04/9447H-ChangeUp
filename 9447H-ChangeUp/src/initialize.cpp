#include "main.h"

#include "class/displayController.hpp"
#include "class/control/intakes.hpp"

Display display;
static Intake intake;

void initialize() {
  display.setup();
  intake.iiInit();
if(isSetup){display.destroy();}
}

void disabled(){}

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
