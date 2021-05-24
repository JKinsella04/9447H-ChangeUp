#pragma once
#include "main.h"
#include "globals.hpp"

#define RIGHT 1
#define LEFT 2
#define HOLD 1
#define COAST 2
#define CIRCUMFERENCE 10.21018

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
    Sets the drive base motors to either HOLD or COAST

    @param int state_ The State of the motor
    */
    void setState(int state_);

    /*
    resets variables and stops motors. For ending drive + driveCurve.
    */
    void stop();

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
    Calculate whether to turn right or left. Is called Automatically in Chassis::turn();

    @param current_Pos current heading
    @param target_Pos wanted heading
    */
    void calcDir(int current_Pos, int target_Pos);

    /*
    Turn with just the left wheels.

    @param oneSide_ bool 1 for only left side 0 for both.
    */
    Chassis& justOneSide(bool oneSide_);

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

    Chassis& driveCurve(double target, double turn_kP, double turn_kD);

    /*
    Sets halt boolean. Controls whether motors stop moving after reaching tolerance.

    @param halt_ 1 to stop motors.
    */
    void waitUntilSettled(bool halt_ = 1);

    /*
    Sets turn Variables used in Chassis::move();

    @param theta_ wanted angle.
    @param turn_kP_ kP constant.
    @param turn_kI_ kI constant.
    @param turn_kD_ kD constant.

    */
    Chassis& withTurn(double theta_, double turn_kP_, double turn_kI_, double turn_kD_);

    /*
    Sets drive Variables.

    @param target wanted distance in inches.
    @param drive_kP_ kP constant.
    @param drive_kI_ kI constant.
    @param drive_kD_ kD constant.

    */
    Chassis& move(double target, double drive_kP, double drive_kI, double drive_kD);

  private:
    static bool isSettled, autoSort_enabled;

    static double leftheading, middleheading, rightheading, averageheading;

    static double power, rate_drive, rate_turn;
    static double kP_drive, kI_drive, kD_drive, kP_turn, kD_turn;
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
    static int heading_diff;
    static bool oneSide;
    static double turnPrevError;

    static bool halt;
    static double turn_output;
    static double m_error, m_integral, m_derivative, m_prevError, m_power, LOutput, ROutput;
    static double t_error, t_integral, t_derivative, t_prevError, t_power, theta, turn_kP, turn_kI, turn_kD;

};
