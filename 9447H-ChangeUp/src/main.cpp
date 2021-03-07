#include "main.h"
#include "globals.hpp"

#include "class/control/auton.hpp"
#include "class/control/intakes.hpp"
#include "class/control/slew.hpp"
#include "class/displayController.hpp"


Display display;
Auton auton;
static Intake intake;
static Slew slew;


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

void opcontrol() {
  // intake.deploy();
  while (true) {
    printf("Left, Right: %d %d\n", LOdometer.get_position(), ROdometer.get_position());
    printf("LOptical, ROptical: %d %d\n", LOptical.get_proximity(), ROptical.get_proximity());
    slew.tankDrive(900, 500, 900);
    intake.runIntakes();
    pros::delay(15);
  }
}
void autonomous() {
  // printf("startPos, firstPos, secondPos, thirdPos %d %d %d %d \n", startPos, firstPos, secondPos, thirdPos);
  // if(alliance == 3){auton.runSkills();} //If Skills was selected it will run skills else it will build the auton.
  // else{auton.run();}
  auton.runTests();
}
