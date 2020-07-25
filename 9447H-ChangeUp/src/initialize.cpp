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
  display.arcchecker();
  display.setVars();
  pros::delay(20);}
}
