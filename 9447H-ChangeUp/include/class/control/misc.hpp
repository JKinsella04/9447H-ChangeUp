#pragma once
#include "main.h"
#include "globals.hpp"

class motionProfile{
  public:

    struct profile{
      double avgV;
      double maxV;
      double totalTime;
      double totalDist;
      double sustainedV;
      double sustainedTime;
      double sustainedDist;
      double accel;
    }; profile linear;

    /*
    caclulate Avg Velocity based off arguments

    @param dist_ distance in inches
    @param time_ time in seconds
    */
    double calcAvgVelocity();

    /*
    calculate max velocity.
    */
    double calcMaxVelocity();
    /*
    returns Avg Velocity
    */
    double getAvgVelocity();

    double calcSustainedTime();

    /*
    calculate total distance.
    */
    double calcTotalDistance();

    double calcAccel();


    double convertTime();

    motionProfile& calculate(double totalDist_, double totalTime_);

    motionProfile& drive();

  private:
    static double LOutput, ROutput, milliTime;
};
