#include "main.h"
#include "globals.h"

class Slew {
  public:
    /*
    Starts Driver Slew code with the given acceleration.

    @param accel Acceleration
    */
    int driveSlew(double accel);

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
    double LslewOutput = 0, RslewOutput = 0, IntakeOutput =0, IndexerOutput =0, middleIntakeOutput =0;
    double IslewMax = 600, IslewMin = -600, middleIntakeMax = 400, middleIntakeMin  = -600; //Real Robot 600 RPM
    double leftJoystick, rightJoystick, leftError, rightError;
};
