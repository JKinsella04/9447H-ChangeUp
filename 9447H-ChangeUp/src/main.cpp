#include "main.h"
#include "globals.hpp"

#include "class/control/auton.hpp"
#include "class/control/intakes.hpp"
#include "class/control/slew.hpp"
#include "class/displayController.hpp"


Display display;
Auton auton;
static Intake intake;
static Slew slew;

/*
Task Creation for Driver Control
*/


void initialize() {
  display.setup();
  intake.iiInit();
  if(isSetup){display.destroy();}
}


void disabled(){}

void competition_initialize() {
  display.display();
  while(1){
    display.backgroundcheck();
    while(alliance==0){display.setAlliance(); pros::delay(15);}
      display.arcChecker();
      display.setVars();
      display.updateSensors();
  pros::delay(20);}
}

void opcontrol() {
  pros::Task intakeTask(Intake::runIntakes);
  intake.intakeLock();
  while (true) {
    printf("Left, Right: %d %d\n", LOdometer.get_position(), ROdometer.get_position());
    slew.tankDrive(900, 500, 900);
    // if(master.get_digital(DIGITAL_R1)){
    //   intake.twoBall(1);
    // }else if (master.get_digital(DIGITAL_R2)){
    //   intake.twoBall(0);
    // }
    // if(master.get_digital(DIGITAL_L1)){
    //   intake.goalSort(alliance);
    // }else{
    //   intake.intakeStop();
    //   intake.rollerStop();
    //   // intake.stopped = 1;
    // }
    // intake.runIntakes();
    // intakeTask.set_priority(TASK_PRIORITY_DEFAULT+1);
    // intakeTask.
    pros::delay(15);
  }
}
void autonomous() {
//   std::shared_ptr<ChassisController> myChassis =
//   ChassisControllerBuilder()
//     .withMotors({1, 2}, {-3, -4})
//     // Green gearset, 4 in wheel diam, 11.5 in wheel track
//     .withDimensions(AbstractMotor::gearset::blue, {{3.25_in, 11.5_in}, imev5GreenTPR})
//     .build();
//
// std::shared_ptr<AsyncMotionProfileController> profileController =
//   AsyncMotionProfileControllerBuilder()
//     .withLimits({
//       1.0, // Maximum linear velocity of the Chassis in m/s
//       2.0, // Maximum linear acceleration of the Chassis in m/s/s
//       10.0 // Maximum linear jerk of the Chassis in m/s/s/s
//     })
//     .withOutput(myChassis)
//     .buildMotionProfileController();
//
//   profileController->generatePath({
//   {0_ft, 0_ft, 0_deg},  // Profile starting position, this will normally be (0, 0, 0)
//   {3_ft, 0_ft, 0_deg}}, // The next point in the profile, 3 feet forward
//   "A" // Profile name
//   );
//   profileController->setTarget("A");
  // printf("startPos, firstPos, secondPos, thirdPos %d %d %d %d \n", startPos, firstPos, secondPos, thirdPos);
  if(alliance == 3){auton.runSkills();} //If Skills was selected it will run skills else it will build the auton.
  else{auton.run();}
  // auton.runTests();
}
