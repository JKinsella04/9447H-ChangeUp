#include "main.h"
#include "globals.hpp"

class Slew {
  public:
    /*
    Starts Drive Tank Control with the given slew values.

    @param fwdAccel Forward acceleration rate.
    @param deccel Decceleration rate.
    @param revAccel Reverse/backward accerleration rate.
    */
    int tankDrive(double fwdAccel, double deccel, double revAccel);

  private:
    static int LslewOutput, RslewOutput;
    static int driveMax;
    static int leftJoystick, rightJoystick;
    static int leftSide, rightSide;
    static int rightTarget, leftTarget;
};
