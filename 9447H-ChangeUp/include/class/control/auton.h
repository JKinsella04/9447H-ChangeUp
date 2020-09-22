#include "main.h"
#include "globals.h"

#include "class/displayController.h"

class Auton {
  public:
    /*
    Uses variables set from Display::loadAuton to build and run the Auton
    */
    Auton& run();

    /*
    Runs the Skills autonomous.
    */
    Auton& runSkills();

  private:

};
