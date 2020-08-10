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

void Intake::iiInit(){
  leftIntake.set_brake_mode(MOTOR_BRAKE_COAST);
  middleIntake.set_brake_mode(MOTOR_BRAKE_COAST);
  rightIntake.set_brake_mode(MOTOR_BRAKE_COAST);
  indexer.set_brake_mode(MOTOR_BRAKE_COAST);
}

void Intake::iiLock(){
  leftIntake.set_brake_mode(MOTOR_BRAKE_HOLD);
  middleIntake.set_brake_mode(MOTOR_BRAKE_HOLD);
  rightIntake.set_brake_mode(MOTOR_BRAKE_HOLD);
  indexer.set_brake_mode(MOTOR_BRAKE_HOLD);
}

Intake& Intake::autoSort(){

  return *this;
}
