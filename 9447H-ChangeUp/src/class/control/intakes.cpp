#include "globals.h"

#include "class/control/intakes.h"

pros::vision_signature_s_t REDBALL_SIG = pros::Vision::signature_from_utility(REDBALL, 8497, 10143, 9320, -319, 1185, 434, 3.000, 0);
pros::vision_signature_s_t BLUEBALL_SIG = pros::Vision::signature_from_utility(BLUEBALL, -4111, -3209, -3660, -2213, -1065, -1640, 3.000, 0);


void Intake::intakeSpin(int speed){
  leftIntake.move(speed);
  rightIntake.move(speed);
}

void Intake::intakeSpin(double ecount, int speed){
  leftIntake.move_relative(ecount, speed);
  pros::delay(50);
  rightIntake.move_relative(ecount, speed);
}

void Intake::intakeStop(){
  leftIntake.move(0);
  rightIntake.move(0);
}

void Intake::indexerSpin(int speed){
  indexer.move(speed);
}

void Intake::indexerSpin(int ecount, int speed){
  indexer.move(speed);
  pros::delay(ecount);
  indexerStop();
}

void Intake::indexerStop(){
  indexer.move(0);
}

void Intake::middleSpin(int speed){
  middleIntake.move(speed);
}

void Intake::middleSpin(int ecount, int speed){
  middleIntake.move_relative(ecount, speed);
}

void Intake::middleStop(){
  middleIntake.move(0);
}

void Intake::runIntakes(){
  if(master.get_digital(DIGITAL_L1) ==1)intakeSpin(600);
  else if(master.get_digital(DIGITAL_L2) ==1)intakeSpin(-600);
  else if(master.get_digital(DIGITAL_L1) !=1 && master.get_digital(DIGITAL_L2) !=1 && master.get_digital(DIGITAL_A) !=1 && master.get_digital(DIGITAL_Y) !=1){ intakeStop();}
  if(master.get_digital(DIGITAL_R2) ==1){indexerSpin(-400); middleSpin(400);}
  else if(master.get_digital(DIGITAL_R1) ==1){indexerSpin(600); middleSpin(600);}
  else if(master.get_digital(DIGITAL_Y) ==1){intakeSpin(-600); middleSpin(-600); indexerSpin(-600);}
  else if(master.get_digital(DIGITAL_R1) !=1 && master.get_digital(DIGITAL_R2) !=1 && master.get_digital(DIGITAL_Y) !=1 && master.get_digital(DIGITAL_A) !=1){indexerStop(); middleStop();}
  if(master.get_digital(DIGITAL_L1) !=1 && master.get_digital(DIGITAL_L2) !=1 && master.get_digital(DIGITAL_R1) !=1 && master.get_digital(DIGITAL_R2) !=1 && master.get_digital(DIGITAL_A) !=1 && master.get_digital(DIGITAL_Y) !=1){intakeStop(); indexerStop(); middleStop();}
}

void Intake::runAutoIndexer(){
  if(master.get_digital(DIGITAL_A) == 1){
    double midLightAverage = botLight.get_value(); //+ topLight.get_value())/2;
    double topLightAverage = topLight.get_value();
    if(topLightAverage <=2200){
      indexerStop();
      topFull=1;
      if(midLightAverage >= 2200){
        middleSpin(600);}
      else{
        middleStop();
        middleFull=1;
       }
     }
    else{
    intakeSpin(600);
    middleSpin(600);
    indexerSpin(600);
    topFull=0;
  }
  printf("lightAverage  %F \n",midLightAverage);
}// else if(master.get_digital(DIGITAL_R1) !=1 && master.get_digital(DIGITAL_R2) !=1 && master.get_digital(DIGITAL_Y) !=1 && master.get_digital(DIGITAL_A)){indexerStop(); middleStop();}
}

void Intake::iiInit(){
  leftIntake.set_brake_mode(MOTOR_BRAKE_COAST);
  middleIntake.set_brake_mode(MOTOR_BRAKE_COAST);
  rightIntake.set_brake_mode(MOTOR_BRAKE_COAST);
  indexer.set_brake_mode(MOTOR_BRAKE_COAST);
  leftIntake.tare_position();
  rightIntake.tare_position();
  middleIntake.tare_position();
  indexer.tare_position();
}

void Intake::iiLock(){
  leftIntake.set_brake_mode(MOTOR_BRAKE_HOLD);
  middleIntake.set_brake_mode(MOTOR_BRAKE_HOLD);
  rightIntake.set_brake_mode(MOTOR_BRAKE_HOLD);
  indexer.set_brake_mode(MOTOR_BRAKE_HOLD);
}

void Intake::deploy(){
  iiInit();
  indexerSpin(50,-600);
  intakeSpin(-3,-600);
  pros::delay(500);
}
void Intake::calculateSort(int opposingColor){
  while (true) {
    pros::vision_object_s_t latestsnapshot = vis.get_by_sig(0, opposingColor);
    std::cout << "sig:" << latestsnapshot.signature << std::endl; //debug
    if(latestsnapshot.signature != 0){/*do mvmt to send out back*/}
    pros::delay(2);
  }
}

Intake& Intake::autoSort(){
  switch (alliance){
    case 1:{ calculateSort(REDBALL); break;/*Red Alliance*/}
    case 2:{ calculateSort(BLUEBALL); break;/*Blue Alliance*/}
  }
  return *this;
}
