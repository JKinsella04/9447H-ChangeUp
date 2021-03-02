#pragma once

#include "main.h"
#include "globals.hpp"

#include "class/displayController.hpp"

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

    /*
    Function meant to perform any tests during auton phase. 
    */
    Auton& runTests();

  private:

};
