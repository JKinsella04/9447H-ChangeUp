#include "globals.h"

#include "class/control/intakes.h"

void Intake::intakeSpin(int speed){
  leftIntake.move(speed);
  pros::delay(50);
  rightIntake.move(speed);
  pros::delay(50);
  middleIntake.move(speed);
  leftIntake.move(speed);
  pros::delay(50);
  rightIntake.move(speed);
  pros::delay(50);
  middleIntake.move(speed);
}

void Intake::intakeSpin(int ecount, int speed){
  leftIntake.move_relative(ecount, speed);
  pros::delay(50);
  rightIntake.move_relative(ecount, speed);
  pros::delay(50);
  middleIntake.move_relative(ecount, speed);
}

void Intake::indexerSpin(int speed){
  indexer.move(speed);
}

void Intake::indexerSpin(int ecount, int speed){
  indexer.move_relative(ecount, speed);
}

Intake& Intake::autoSort(){

  return *this;
}
