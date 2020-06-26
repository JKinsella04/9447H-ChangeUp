#include "main.h"

#include "class/control/slew.h"

double LslewOutput = 0, RslewOutput = 0;
double LslewError, RslewError;



int Slew::driveSlew(double accel){
while (1){
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

  pros::delay(25);
} //while
  return 0;
}
