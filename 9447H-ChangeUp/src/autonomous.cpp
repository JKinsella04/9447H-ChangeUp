#include "main.h"

#include "class/control/auton.h"

Auton auton;

void autonomous() {
  // printf("startPos, firstPos, secondPos, thirdPos %d %d %d %d \n", startPos, firstPos, secondPos, thirdPos);
  if(alliance == 3){auton.runSkills();} //If Skills was selected it will run skills else it will build the auton.
  else{auton.run();}
  }
