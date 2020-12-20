#include "main.h"

#include "class/control/slew.hpp"

int Slew::LslewOutput =0, Slew::RslewOutput =0;
int Slew::driveMax =0;
int Slew::leftJoystick =0, Slew::rightJoystick =0;
int Slew::leftSide =0, Slew::rightSide=0;
int Slew::leftTarget =0, Slew::rightTarget =0;

int Slew::tankDrive(double fwdAccel, double deccel, double revAccel){
  leftJoystick = master.get_analog(ANALOG_LEFT_Y);
  rightJoystick = master.get_analog(ANALOG_RIGHT_Y);

  double averageJoystick = leftJoystick/rightJoystick;
  printf("leftTarget, LslewOutput, actualPower, %d %d %f\n", leftTarget, LslewOutput, LF.get_actual_velocity());

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
  if(master.get_digital(DIGITAL_L1) && master.get_digital(DIGITAL_L2) && master.get_digital(DIGITAL_R1) && master.get_digital(DIGITAL_R2)){
    if(goalDist.get() <= 50){
      LslewOutput = 0;
      RslewOutput = 0;
    }
  }

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

  leftTarget = 0;

  if(abs(leftSide) <5 ) leftSide = 0;
  if(abs(rightSide) <5 ) rightSide = 0;

  leftTarget = leftJoystick*driveMax; //1.58
  if(LslewOutput < leftTarget){if(leftTarget == 0 && LslewOutput !=0){LslewOutput +=deccel;} else{LslewOutput +=fwdAccel;}}
  if(LslewOutput > leftTarget){if(leftTarget == 0 && LslewOutput !=0){LslewOutput -=deccel;} else{LslewOutput -=revAccel;}}
  // if(leftTarget == 0)LslewOutput = 0;

  rightTarget = rightJoystick*driveMax; //1.58
  if(RslewOutput < rightTarget){if(rightTarget == 0 && RslewOutput !=0){RslewOutput +=deccel;} else{RslewOutput +=fwdAccel;}}
  if(RslewOutput > rightTarget){if(rightTarget == 0 && RslewOutput !=0){RslewOutput -=deccel;} else{RslewOutput -=revAccel;}}
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
