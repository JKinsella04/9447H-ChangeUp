#include "main.h"

#include "class/control/slew.h"


int Slew::driveSlew(double accel){
  if(master.get_analog(ANALOG_LEFT_Y)*1.58 > LslewOutput + accel ) LslewOutput += accel;
  if(master.get_analog(ANALOG_LEFT_Y)*1.58 < LslewOutput + accel ) LslewOutput -= accel;
  if(master.get_analog(ANALOG_RIGHT_Y)*1.58 > RslewOutput + accel ) RslewOutput += accel;
  if(master.get_analog(ANALOG_RIGHT_Y)*1.58 < RslewOutput + accel ) RslewOutput -= accel;
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
  if(master.get_digital(DIGITAL_R1) ==1){
    if(IntakeOutput < IslewMax + intakeAccel) IntakeOutput += intakeAccel;
    if(IndexerOutput < IslewMax + indexerAccel) IndexerOutput += indexerAccel;}
  else if(master.get_digital(DIGITAL_L1) ==1){
    if(IntakeOutput > IslewMin - intakeAccel) IntakeOutput -= intakeAccel;
    if(IndexerOutput > IslewMin - indexerAccel) IndexerOutput -= indexerAccel;}
  else if(master.get_digital(DIGITAL_R2) ==1){
    if(IntakeOutput < IslewMax + intakeAccel) IntakeOutput += intakeAccel;
    if(IndexerOutput > IslewMin - indexerAccel) IndexerOutput -= indexerAccel;}
  else{IndexerOutput =0, IntakeOutput =0;}

  leftIntake.move_velocity(IntakeOutput);
  middleIntake.move_velocity(IntakeOutput);
  rightIntake.move_velocity(IntakeOutput);
  indexer.move_velocity(IndexerOutput);
}
