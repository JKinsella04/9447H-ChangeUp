#include "main.h"

#include "class/control/slew.h"

double POSlimit = 127, MINLimit = -127;

double LslewOutput = 0, RslewOutput = 0;
double LslewError, RslewError;



int Slew::driveSlew(double accel){
while (1){
  if(master.get_analog(ANALOG_LEFT_Y) > LslewOutput + accel ) LslewOutput += accel;
  if(master.get_analog(ANALOG_LEFT_Y) < LslewOutput + accel ) LslewOutput -= accel;
  if(master.get_analog(ANALOG_RIGHT_Y) > RslewOutput + accel ) RslewOutput += accel;
  if(master.get_analog(ANALOG_RIGHT_Y) < RslewOutput + accel ) RslewOutput -= accel;
  LF.move(LslewOutput);
  LB.move(LslewOutput);
  RF.move(-RslewOutput);
  RB.move(-RslewOutput);
  pros::delay(25);
} //while
  return 0;
}
