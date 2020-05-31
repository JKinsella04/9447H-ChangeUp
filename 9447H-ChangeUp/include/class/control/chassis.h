#include "main.h"
#include "globals.h"


class Chassis {
  public:
    Chassis();
    ~Chassis();

    /*
    Zeroes drive base motors and sensors.
    */
    void reset();

    /*
    Resets Odom, IMUs, and Wheel Encoders.
    */
    void SensorReset();

    /*
    Delays the calling thread until the robot completes its action.
    */
    void waitUntilSettled();

    /*
    Sets Turn rate for the slew acceleration.

    @param rate_ Default rate = 5
    */
    Chassis& withTurnSlew(double rate_ = 5);

    /*
    Sets the Turn kP and kD variables.

    @param kP_ The kP variable.
    @param kD_ The kD variable.
    */
    Chassis& withTurnPD(double kP_, double kD_);

    /*
    Sets Drive rate for the slew acceleration.

    @param rate_ Default rate = 5
    */
    Chassis& withSlew(double rate_ =5);
    /*
    Sets Drive kP and kD variables

    @param kP_ The kP variable.
    @param kD_ The kD variable.
    */
    Chassis& withPD(double kP_, double kD_);
    /*
    Turns the robot to a set angle.

    Use withTurnSlew & withTurnPD with this.

    @param theta_ The wanted angle.
    */
    Chassis& turn(double theta_);

    /*
    Drives the robot a set distance

    Use withSlew & withPD with this.

    @param target The wanted distance
    */
    Chassis& drive(double target);

  private:
    static bool isSettled;

    static double leftheading, middleheading, rightheading, averageheading;

    static double power,rate_drive, rate_turn;
    static double kP_drive, kD_drive, kP_turn, kD_turn;
    static int output;
};
