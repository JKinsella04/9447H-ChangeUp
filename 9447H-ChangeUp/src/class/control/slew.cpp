#include "main.h"

#include "class/control/slew.hpp"


int Slew::tankDrive(double fwdAccel, double deccel, double revAccel){
  leftJoystick = master.get_analog(ANALOG_LEFT_Y);
  rightJoystick = master.get_analog(ANALOG_RIGHT_Y);

  double averageJoystick = leftJoystick/rightJoystick;
  printf("leftTarget, LslewOutput, actualPower, %d %f %f\n", leftTarget, LslewOutput, LF.get_actual_velocity());

  if(leftJoystick/rightJoystick < 0 || leftJoystick/rightJoystick >=2){driveMax =9000/127;}else{driveMax=12000/127;}
  if(rightJoystick/leftJoystick < 0 || rightJoystick/leftJoystick >=2){driveMax =9000/127;}else{driveMax=12000/127;}

  leftTarget = 0;

  if(abs(leftJoystick) <5){ leftJoystick = 0;}
  if(abs(rightJoystick) <5){ rightJoystick = 0;}

  leftTarget = leftJoystick*driveMax; //1.58
  if(LslewOutput < leftTarget){if(leftTarget == 0 && LslewOutput !=0){LslewOutput +=deccel;} else{LslewOutput +=fwdAccel;}}
  if(LslewOutput > leftTarget){if(leftTarget == 0 && LslewOutput !=0){LslewOutput -=deccel;} else{LslewOutput -=revAccel;}}
  // if(leftTarget == 0)LslewOutput = 0;

  rightTarget = rightJoystick*driveMax; //1.58
  if(RslewOutput < rightTarget){if(rightTarget == 0 && RslewOutput !=0){RslewOutput +=deccel;} else{RslewOutput +=fwdAccel;}}
  if(RslewOutput > rightTarget){if(rightTarget == 0 && RslewOutput !=0){RslewOutput -=deccel;} else{RslewOutput -=revAccel;}}
  // if(rightTarget == 0)RslewOutput = 0;

  if(master.get_digital(DIGITAL_A)){LslewOutput = 0; RslewOutput = 0;}

  LF.move_voltage(-LslewOutput);
  LB.move_voltage(-LslewOutput);
  RF.move_voltage(RslewOutput);
  RB.move_voltage(RslewOutput);

  return 0;
}

void Slew::arcadeControl(int fwdAccel, int deccel, int revAccel){
  leftSide = master.get_analog(ANALOG_LEFT_Y) + master.get_analog(ANALOG_LEFT_X);
  rightSide = master.get_analog(ANALOG_LEFT_Y) - master.get_analog(ANALOG_LEFT_X);

  if(abs(master.get_analog(ANALOG_LEFT_X)) > 10 ){driveMax =9000;}else{driveMax=12000;}

  if(abs(leftSide) <5 ) leftSide = 0;
  if(abs(rightSide) <5 ) rightSide = 0;

  leftError = leftSide*47.244 - LslewOutput; //1.58
  leftOvershoot = deccel - abs(LslewOutput);
  if(abs(leftError) == 400)LslewOutput = 0;
  if(leftError > 0){if(leftSide == 0){ if(leftOvershoot >0){deccel -= leftOvershoot;}LslewOutput +=deccel;}else if(LslewOutput < driveMax){LslewOutput +=fwdAccel;}}
  if(leftError < 0){if(leftSide == 0){ if(leftOvershoot >0){deccel -= leftOvershoot;}LslewOutput -=deccel;}else if(LslewOutput > -driveMax){LslewOutput -=revAccel;}}
  rightError = rightSide*94.488 - RslewOutput;
  rightOvershoot = deccel - abs(RslewOutput);
  if(abs(rightError) == 400) RslewOutput = 0;
  if(rightError > 0){if(rightSide == 0){ if(rightOvershoot >0){deccel -= rightOvershoot;}RslewOutput +=deccel;}else if(RslewOutput < driveMax){RslewOutput +=fwdAccel;}}
  if(rightError < 0){if(rightSide == 0){ if(rightOvershoot >0){deccel -= rightOvershoot;}RslewOutput -=deccel;}else if(RslewOutput > -driveMax){RslewOutput -=revAccel;}}
  // printf("left, LOutput, leftError  %F %F %F \n", rightJoystick, LslewOutput, RslewOutput);

  if(RslewOutput > 12000)RslewOutput =12000;
  if(LslewOutput > 12000)LslewOutput =12000;

  if(LslewOutput == 0) LF.set_brake_mode(MOTOR_BRAKE_COAST); LB.set_brake_mode(MOTOR_BRAKE_COAST);
  if(RslewOutput == 0) RF.set_brake_mode(MOTOR_BRAKE_COAST); RB.set_brake_mode(MOTOR_BRAKE_COAST);

  LF.move_voltage(-LslewOutput);
  LB.move_voltage(-LslewOutput);
  RF.move_voltage(RslewOutput);
  RB.move_voltage(RslewOutput);

  driveMax = 12000;
}

int Slew::intakeSlew(double accel){
  if(master.get_digital(DIGITAL_L1) == 1){
    if(IntakeOutput < IslewMax + accel) IntakeOutput += accel;}
  else if(master.get_digital(DIGITAL_L2) == 1){
    if(IntakeOutput > IslewMin - accel) IntakeOutput -= accel;}
  else{IntakeOutput =0;}

  leftIntake.move_velocity(IntakeOutput);
  middleIntake.move_velocity(IntakeOutput);
  rightIntake.move_velocity(IntakeOutput);

  return 0;
}

int Slew::indexerSlew(double accel){
  if(master.get_digital(DIGITAL_R1) == 1){
    if(IndexerOutput < IslewMax + accel) IndexerOutput += accel;}
  else if(master.get_digital(DIGITAL_R2) == 1){
    if(IndexerOutput > IslewMin - accel) IndexerOutput -= accel;}
  else{IndexerOutput =0;}

  indexer.move_velocity(IndexerOutput);

  return 0;
}

void Slew::allSlew(double intakeAccel, double indexerAccel){
  if(master.get_digital(DIGITAL_L1) ==1){
    if(IntakeOutput < IslewMax + intakeAccel) IntakeOutput += intakeAccel;}
  else if(master.get_digital(DIGITAL_L2) ==1){
    if(IntakeOutput > IslewMin - intakeAccel) IntakeOutput -= intakeAccel;}
  else if(master.get_digital(DIGITAL_L1) !=1 && master.get_digital(DIGITAL_L2) !=1 && master.get_digital(DIGITAL_R1) !=1 && master.get_digital(DIGITAL_R2) !=1){ IntakeOutput =0;}
  if(master.get_digital(DIGITAL_R2) ==1){
    IntakeOutput = 400, IndexerOutput = -400, middleIntakeOutput = 400;} //else{IntakeOutput =0, IndexerOutput=0, middleIntakeOutput =0;}
  else if(master.get_digital(DIGITAL_R1) ==1 && master.get_digital(DIGITAL_R2) != 1){
      if(IntakeOutput < IslewMax + intakeAccel) IntakeOutput += intakeAccel;
      if(IndexerOutput < IslewMax + indexerAccel) IndexerOutput += indexerAccel;
      if(middleIntakeOutput < middleIntakeMax + intakeAccel) middleIntakeOutput += intakeAccel;}
  else{IndexerOutput =0, middleIntakeOutput =0;} //, IntakeOutput =0

  leftIntake.move_velocity(IntakeOutput);
  middleIntake.move_velocity(middleIntakeOutput);
  rightIntake.move_velocity(IntakeOutput);
  indexer.move_velocity(IndexerOutput);
}
