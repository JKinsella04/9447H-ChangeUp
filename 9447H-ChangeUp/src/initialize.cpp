#include "main.h"
#include "class/control/chassis.h"
#include "class/displayController.h"

void initialize() {
}


void competition_initialize() {
    Chassis chassis;
    Display display;

    chassis.reset();
    display.display();
    while(1){
    display.backgroundcheck().arcchecker();
    pros::delay(20);
  }
}
