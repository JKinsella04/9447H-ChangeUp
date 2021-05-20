#pragma once
#include "main.h"
#include "globals.hpp"

#define REDBALL 1
#define BLUEBALL 2
#define HOLDBALL 0
#define SHOOTBALL 1


class Intake{
  public:
    /*
    Spins intakes at given voltage with the range of -12,000-12,000.

    @param speed RPM
    */
    static void intakeSpin(int speed);

    /*
    Spins intakes for the given amount of encoder counts in RPM.

    @param ecount encounder counts
    @param speed RPM
    */
    void intakeSpin(double ecount, int speed);

    /*
    Spins intakes at given rpm to the max of the gearset of the motor

    @param velocity RPM
    */
    void intakeSpinVelocity(int velocity);

    /*
    Sets intakes to 0 RPM.
    */
    static void intakeStop();

    /*
    Spins the rolelrs. For Ohio style rollers (All connected)
    */
    static void rollerSpin(int speed);

    /*
    Stops the rollers. For Ohio style rollers (ALL connected)
    */
    static void rollerStop();

    /*
    Spins indexer at given voltage with the range of -12,000-12,000.

    @param speed RPM
    */
    void indexerSpin(int speed);

    /*
    Spins indexer for the given amount of encoder counts in RPM.

    @param ecount encoder counts
    @param speed rpm
    */
    void indexerSpin(int ecount, int speed);

    /*
    Spins the indexer at given RPM to the max of the gearset of the motor

    @param velocity RPM
    */
    void indexerSpinVelocity(int velocity);

    /*
    Sets indexer to 0 RPM.
    */
    void indexerStop();

    /*
    Spins middle intake at given voltage with the range of -12,000-12,000.

    @param speed RPM
    */
    void middleSpin(int speed);

    /*
    Spins middleIntake for the vien amount of encoder counts in RPM.

    @param ecount encoder counts
    @param speed rpm
    */
    void middleSpin(int ecount, int speed);

    /*
    Spins the middle intake at given RPM to the max of the gearset of the motor

    @param velocity RPM
    */
    void middleSpinVelocity(int velocity);

    /*
    Sets middleIntake to 0 RPM.
    */
    void middleStop();

    /*
    Runs the intakes for driver control.
    */
    static void runIntakes();

    /*
    Initializes both the intakes and the indexers.
    */
    void iiInit();

    /*
    Sets both intakes and indexers to Hold
    */
    void intakeLock();

    /*
    Deploys the hood and intakes. Run at the beginning of driver control and pre-auton
    */
    void deploy();

    /*
    To set how many balls (1 or 2) are being taken from goal.
    Call with goalSort();
    @param twoBall_ bool 1 for true 0 for false..
    */
    Intake& twoBall(bool twoBall_);

    /*
    Sorts out the enemy ball based on color.
    The opposing color is determined during the auton selection before a match.

    @param allianceColor Color of user's alliance.
    */
    static void autoSort(int allianceColor = alliance);

    /*
    Sorts out the enemy ball based on color.
    This is used to auto sort while interacting with the gaols.

    @param allianceColor Color of user's alliance.
    */
    static void goalSort(int allianceColor);

    /*
    Runs the goalSort for an amount of time.

    @param int allianceColor your alliance REDBALL or BLUEBALL
    @param int time length of the timer
    @param bool state whether you want to hold the balls or shoot them out.
    */
    void goalSort(int allianceColor, int time, bool state = SHOOTBALL);

    /*
    Runs the indexer and shortly after the middleIntake to shoot two balls out the back of the robot.
    Recommended to run this shortly after calling goalSort() with state HOLDBALL.

    @param drop_Mode Accepts either EJECT or REVERSE. Determines how the ball(s) leaves the robot.
    */
    void dropBall();

    /*
    Cycles through LED brightness to get the wanted resting value for the Optical sensors.

    @param resting_value Value you want the optical sensors to rest at when not detecting anything.
    */
    void calibrate(int resting_value);

  private:
    static int ledLevel, redHue, blueHue, time, ballsLeft;
    static bool oneBall, pos1, pos2, stopped, ball, twoBalls;
};
