#pragma once
#include "main.h"
#include "globals.hpp"

#define RIGHT 1
#define LEFT 2
#define HOLD 1
#define COAST 2

class Chassis {
  public:
    Chassis();
    ~Chassis();

    /*
    Zeroes drive base motors and sensors.
    */
    void reset();

    /*
    Resets Odom sensors.
    */
    void odomReset();

    /*
    Delays the calling thread until the robot completes its action.
    */
    void waitUntilSettled();

    /*
    Sets the drive base motors to either HOLD or COAST

    @param int state_ The State of the motor
    */
    void setState(int state_);

    /*
    Sets Turn rate for the slew acceleration.

    @param rate_ Default rate = 5
    */
    Chassis& withTurnSlew(double rate_ = 1);

    /*
    Sets the Turn kP and kD variables.

    @param kP_ The kP variable.
    @param kD_ The kD variable.
    */
    Chassis& withTurnPD(double kP_, double kD_);

    /*
    Sets the direction you want to turn

    @param direction_turn_ Either RIGHT or LEFT.
    */
    Chassis& withTurnDirection(int direction_turn_);

    /*
    If called it will run the autoSort function while driving or turning.

    @param autoSort_enabled_ Boolean for whether autosorting is enabled.
    */
    Chassis& autoSort(bool autoSort_enabled_ = 0);

    /*
    Sets Drive rate for the slew acceleration.

    @param rate_ Default rate = 5
    */
    Chassis& withSlew(double rate_ =1);
    /*
    Sets Drive kP and kD variables

    @param kP_ The kP variable.
    @param kD_ The kD variable.
    */
    Chassis& withPD(double kP_, double kD_);

    /*
    Sets the wanted angle for the robot to stick to while driving.

    @param theta_ The wanted angle.
    @param correction_rate_ The amount you want to correct by. Default 1.
    */
    Chassis& withHeading(double drive_theta_, double correction_rate_ = 1);

    /*
    Sets justPD Boolean

    @param justPD_ boolean for running just PD no slew.
    */
    Chassis& justPD(bool justPD_);


    /*
    When called with Drive it will stop the drive function if it deteects something in the distance sensor an amount away.

    @param distTarget_ wanted distance from the target
    */
    Chassis& withDist(double distTarget_);

    /*
    Sets tolerance for both drive and turn.

    @param tol_ tolerance
    */
    Chassis& withTol(int tol_ = 10);

    /*
    Turns the robot to a set angle.

    Use withTurnSlew & withTurnPD with this.
    Slew rate control controls the speed of the turning until the speed of the slew rate and the PD loop meet then the PD loop takes control.

    @param theta_ The wanted angle.
    */
    Chassis& turn(double theta_);

    /*
    Drives the robot a set distance

    Use withSlew & withPD with this.
    Slew rate control controls the speed of the turning until the speed of the slew rate and the PD loop meet then the PD loop takes control.

    @param target The wanted distance
    */
    Chassis& drive(double target);

    /*
    drive until you reach certain distance.

    @param dist target distance.
    */
    Chassis& driveDistAway(double dist);
  private:
    static bool isSettled, autoSort_enabled;

    static double leftheading, middleheading, rightheading, averageheading;

    static double power, rate_drive, rate_turn;
    static double kP_drive, kD_drive, kP_turn, kD_turn;
    static double correction_rate;
    static int direction_turn;
    static double output;
    static int slew_a, slew_x;
    static int drive_theta;
    static bool justPID;
    static double distTarget;
    static bool distSensorEnabled;
    static int tol;
    static double prevError; 
};
