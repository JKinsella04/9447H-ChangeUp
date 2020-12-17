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

    /*
    Starts Driver arcade control with given slew values.

    @param fwdAccel Forward acceleration rate.
    @param deccel Decceleration rate.
    @param revAccel Reverse/backward accerleration rate.
    */
    void arcadeControl(int fwdAccel, int deccel, int revAccel);

    /*
    Starts Intake Slew code with the given accerleration.

    @param accel Accerleration
    */
    int intakeSlew(double accel);

    /*
    Starts Indexer Slew code with the given accerleration.

    @param accel Acceleration
    */
    int indexerSlew(double accel);

    /*
    Spins both indexer and intakes with given acceleration for both.

    @param intakeAccel Default 100
    @param indexerAccel Default 100
    */
    void allSlew(double intakeAccel = 100, double indexerAccel = 100);

  private:
    static int LslewOutput, RslewOutput;
    static int driveMax;
    static int leftJoystick, rightJoystick;
    static int leftSide, rightSide;
    static int rightTarget, leftTarget;
};
