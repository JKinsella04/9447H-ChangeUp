#include "misc.hpp"

double motionProfile::LOutput = 0, motionProfile::ROutput= 0, motionProfile::milliTime = 0;

double motionProfile::calcAvgVelocity(){
  linear.avgV = linear.totalDist/linear.totalTime;
  return linear.avgV;
}

double motionProfile::calcMaxVelocity(){
  linear.maxV = 2*linear.avgV;
  return linear.maxV;
}

double motionProfile::calcSustainedTime(){
  linear.sustainedTime = linear.sustainedDist/linear.maxV;
  return linear.sustainedTime;
}

double motionProfile::calcTotalDistance(){
  linear.totalDist = 2/3 * linear.totalTime * linear.totalDist;
  return linear.totalDist;
}

double motionProfile::calcAccel(){
  linear.accel = ((4.5 * linear.totalDist) / pow(linear.totalTime, 2));
  return linear.accel;
}

double motionProfile::convertTime(){
  // linear.totalTime()
  return 0;
}

motionProfile& motionProfile::calculate(double totalDist_, double totalTime_){
  linear.totalDist = totalDist_;
  linear.totalTime = totalTime_;
  milliTime = linear.totalTime * 1000;

  linear.avgV = linear.totalDist/linear.totalTime;
  linear.maxV = 2*linear.avgV;
  linear.accel = ( (4.5 * linear.totalDist) / pow(linear.totalTime, 2) );
  printf("accel: %f totalDist: %f totalTime %f AvgV: %f MaxV: %f \n", linear.accel, linear.totalDist, linear.totalTime, linear.avgV, linear.maxV);
  return *this;
}
motionProfile& motionProfile::drive(){
  for(int i = 0; i < (milliTime)/3; i++ ){
    LOutput += linear.accel;
    ROutput += linear.accel;
    printf("accel: %f LOutput: %f \n", linear.accel, LOutput);
    LF.move_velocity(LOutput);
    LB.move_velocity(LOutput);
    RF.move_velocity(ROutput);
    RB.move_velocity(ROutput);
    if(LOutput >= linear.maxV){ LOutput = linear.maxV; ROutput = linear.maxV; break;}
    pros::delay(1);
    }
  for(int i = 0; i < (milliTime)/3; i++ ){
    printf("accel: %f LOutput: %f \n", linear.maxV, LOutput);
    LF.move_velocity(linear.maxV);
    LB.move_velocity(linear.maxV);
    RF.move_velocity(linear.maxV);
    RB.move_velocity(linear.maxV);
    pros::delay(10);
  }
  for(int i = 0; i < (milliTime)/3; i++ ){
    LOutput -= linear.accel;
    ROutput -= linear.accel;
    LF.move_velocity(LOutput);
    LB.move_velocity(LOutput);
    RF.move_velocity(ROutput);
    RB.move_velocity(ROutput);
    pros::delay(10);
  }
  return *this;
}
