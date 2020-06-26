#include "main.h"
#include "globals.h"

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
    Spins indexer at given RPM

    @param speed RPM
    */
    void indexerSpin(int speed);

    /*
    Spins indexer for the given amount of encoder counts in RPM.

    @param ecount encounder counts
    @param speed rpm
    */
    void indexerSpin(int ecount, int speed);

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
