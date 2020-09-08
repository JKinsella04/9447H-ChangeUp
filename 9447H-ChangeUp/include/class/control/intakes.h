#include "main.h"
#include "globals.h"

#define REDBALL 1
#define BLUEBALL 2

class Intake{
  public:
    /*
    Spins intakes at given RPM

    @param speed RPM
    */
    void intakeSpin(int speed);

    /*
    Spins intakes for the given amount of encoder counts in RPM.

    @param ecount encounder counts
    @param speed RPM
    */
    void intakeSpin(int ecount, int speed);

    /*
    Sets intakes to 0 RPM.
    */
    void intakeStop();

    /*
    Spins indexer at given RPM

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
    Sets indexer to 0 RPM.
    */
    void indexerStop();

    /*
    Spins middle intake at given RPM.

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
    Sets middleIntake to 0 RPM. 
    */
    void middleStop();

    /*
    Runs the intakes for driver control.
    */
    void runIntakes();

    /*
    Initializes both the intakes and the indexers.
    Default moode is coast. To make them hold use iiLock.
    */
    void iiInit();

    /*
    Sets both intakes and indexers to Hold
    */
    void iiLock();

    /*
    Automatically sorts the balls. The Auton builder inputs opposingColor based on ddlist(Alliance)

    @param opposingColor The color of the opposing alliance.
    */
    void calculateSort(int opposingColor);

    /*
    Sorts out the enemy ball based on color.
    The opposing color is determined during the auton selection before a match.
    */
    Intake& autoSort();

    /*
    Delays the calling thread until the robot completes its action.
    */
    void waitUntilSettled();

  private:
};
