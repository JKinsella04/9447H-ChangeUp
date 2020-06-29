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

  private:
    double LslewOutput = 0, RslewOutput = 0, IntakeOutput =0, IndexerOutput =0;
    double LslewError, RslewError;
    double IslewMax = 200, IslewMin = -200; //Real Robot 600 RPM
};
