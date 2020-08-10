#include "main.h"

#include "class/control/slew.h"


int Slew::driveSlew(double accel){
  leftJoystick = master.get_analog(ANALOG_LEFT_Y);
  rightJoystick = master.get_analog(ANALOG_RIGHT_Y);
  if(leftJoystick > 0 && rightJoystick > 0) if(leftJoystick/rightJoystick <0 || leftJoystick/rightJoystick >=2 )leftJoystick = 80, rightJoystick = 80;
  if(leftJoystick > 0 && rightJoystick < 0) if(leftJoystick/rightJoystick <0 || leftJoystick/rightJoystick >=2 )leftJoystick = 80, rightJoystick = -80;
  if(leftJoystick < 0 && rightJoystick > 0) if(leftJoystick/rightJoystick <0 || leftJoystick/rightJoystick >=2 )leftJoystick = -80, rightJoystick = 80;
  if(leftJoystick < 0 && rightJoystick < 0) if(leftJoystick/rightJoystick <0 || leftJoystick/rightJoystick >=2 )leftJoystick = -80, rightJoystick = -80;
  if(leftJoystick > 0 && rightJoystick == 0) if(leftJoystick/rightJoystick <0 || leftJoystick/rightJoystick >=2 )leftJoystick = 80, rightJoystick = 0;
  if(leftJoystick < 0 && rightJoystick == 0) if(leftJoystick/rightJoystick <0 || leftJoystick/rightJoystick >=2 )leftJoystick = -80, rightJoystick = 0;
  if(leftJoystick == 0 && rightJoystick > 0) if(rightJoystick/leftJoystick <0 || rightJoystick/leftJoystick >=2 )leftJoystick = 0, rightJoystick = 80;
  if(leftJoystick == 0 && rightJoystick < 0) if(rightJoystick/leftJoystick <0 || leftJoystick/rightJoystick >=2 )leftJoystick = 0, rightJoystick = -80;

  leftError = leftJoystick*1.58 - LslewOutput;
  if(leftError > 0)LslewOutput +=accel;
  if(leftError < 0)LslewOutput -=accel;
  rightError = rightJoystick*1.58 - RslewOutput;
  if(rightError > 0)RslewOutput +=accel;
  if(rightError < 0)RslewOutput -=accel;
  printf("left, LOutput, leftError  %F %F %F \n", rightJoystick, RslewOutput, rightError);

  if(master.get_analog(ANALOG_LEFT_Y) < 5 && master.get_analog(ANALOG_LEFT_Y) > -5 ) LslewOutput = 0;
  if(master.get_analog(ANALOG_RIGHT_Y) < 5 && master.get_analog(ANALOG_RIGHT_Y) > -5 ) RslewOutput = 0;
  LF.move_velocity(LslewOutput);
  LB.move_velocity(LslewOutput);
  RF.move_velocity(-RslewOutput);
  RB.move_velocity(-RslewOutput);

  return 0;
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
  if(master.get_digital(DIGITAL_R1) ==1 && master.get_digital(DIGITAL_R2) != 1){
    if(IntakeOutput < IslewMax + intakeAccel) IntakeOutput += intakeAccel;
    if(IndexerOutput < IslewMax + indexerAccel) IndexerOutput += indexerAccel;
    if(middleIntakeOutput < middleIntakeMax + intakeAccel) middleIntakeOutput += intakeAccel;}
  else if(master.get_digital(DIGITAL_L1) ==1){
    if(IntakeOutput > IslewMin - intakeAccel) IntakeOutput -= intakeAccel;
    if(IndexerOutput > IslewMin - indexerAccel) IndexerOutput -= indexerAccel;
    if(middleIntakeOutput > middleIntakeMin - intakeAccel) middleIntakeOutput -= intakeAccel;}
  else if(master.get_digital(DIGITAL_R2) ==1){
    IntakeOutput = 400, IndexerOutput = -400;}
  else{IndexerOutput =0, IntakeOutput =0, middleIntakeOutput =0;}

  leftIntake.move_velocity(IntakeOutput);
  middleIntake.move_velocity(middleIntakeOutput);
  rightIntake.move_velocity(IntakeOutput);
  indexer.move_velocity(IndexerOutput);
}
