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

  if(leftJoystick/rightJoystick < 0 || leftJoystick/rightJoystick >=2 || rightJoystick/leftJoystick < 0 || rightJoystick/leftJoystick >=2){driveMax =9000/127;}else{driveMax=12000/127;}

  // leftTarget = 0;

  if(abs(leftJoystick) <5){ leftJoystick = 0;}
  if(abs(rightJoystick) <5){ rightJoystick = 0;}

  leftTarget = leftJoystick*driveMax; //1.58
  if(LslewOutput < leftTarget){if(leftTarget == 0 && LslewOutput !=0){LslewOutput = 0;} else{LslewOutput +=fwdAccel;}}
  if(LslewOutput > leftTarget){if(leftTarget == 0 && LslewOutput !=0){LslewOutput = 0;} else{LslewOutput -=revAccel;}}
  // if(leftTarget == 0)LslewOutput = 0;

  rightTarget = rightJoystick*driveMax; //1.58
  if(RslewOutput < rightTarget){if(rightTarget == 0 && RslewOutput !=0){RslewOutput = 0;} else{RslewOutput +=fwdAccel;}}
  if(RslewOutput > rightTarget){if(rightTarget == 0 && RslewOutput !=0){RslewOutput = 0;} else{RslewOutput -=revAccel;}}
  // if(rightTarget == 0)RslewOutput = 0;

  // if(RslewOutput > 12000)RslewOutput = 12000;
  // if(LslewOutput > 12000)LslewOutput = 12000;


  LF.move_voltage(LslewOutput);
  LB.move_voltage(LslewOutput);
  RF.move_voltage(RslewOutput);
  RB.move_voltage(RslewOutput);

  return 0;
}
