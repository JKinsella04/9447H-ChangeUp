#include "globals.h"

#include "class/control/intakes.h"

int Intake::ledLevel = 75;

void Intake::intakeSpin(int speed){
  leftIntake.move(speed);
  rightIntake.move(speed);
}

void Intake::intakeSpin(double ecount, int speed){
  leftIntake.move_relative(ecount, speed);
  pros::delay(50);
  rightIntake.move_relative(ecount, speed);
}

void Intake::intakeSpinVelocity(int velocity){
  leftIntake.move_velocity(velocity);
  rightIntake.move_velocity(velocity);
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

void Intake::indexerSpinVelocity(int velocity){
  indexer.move_velocity(velocity);
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

void Intake::middleSpinVelocity(int velocity){
  middleIntake.move_velocity(velocity);
}

void Intake::middleStop(){
  middleIntake.move(0);
}

void Intake::runIntakes(){ // Runs the intakes based on L1,L2,R1,R2 and, Y and if they are pressed.
  if(master.get_digital(DIGITAL_L1) ==1 && master.get_digital(DIGITAL_R1)!=1)autoSort(alliance);//runAutoIndexer();
  else if(master.get_digital(DIGITAL_L1) ==1 && master.get_digital(DIGITAL_R1)==1)goalSort(alliance);
  else if(master.get_digital(DIGITAL_L2) ==1)intakeSpin(-600);
  else if(master.get_digital(DIGITAL_L1) !=1 && master.get_digital(DIGITAL_L2) !=1 && master.get_digital(DIGITAL_Y) !=1){ intakeStop();}
  if(master.get_digital(DIGITAL_R2) ==1){indexerSpin(-400); middleSpin(400);if(master.get_digital(DIGITAL_L2) ==1){intakeSpin(600);}}
  else if(master.get_digital(DIGITAL_R1) ==1 && master.get_digital(DIGITAL_L1) !=1){indexerSpin(600); middleSpin(600);if(master.get_digital(DIGITAL_L2) ==1){intakeSpin(600);}}
  else if(master.get_digital(DIGITAL_Y) ==1){intakeSpin(-600); middleSpin(-600); indexerSpin(-600);}
  else if(master.get_digital(DIGITAL_R1) !=1 && master.get_digital(DIGITAL_R2) !=1 && master.get_digital(DIGITAL_Y) !=1 && master.get_digital(DIGITAL_L1) !=1){indexerStop(); middleStop();}
  if(master.get_digital(DIGITAL_L1) !=1 && master.get_digital(DIGITAL_L2) !=1 && master.get_digital(DIGITAL_R1) !=1 && master.get_digital(DIGITAL_R2) !=1 && master.get_digital(DIGITAL_Y) !=1){intakeStop(); indexerStop(); middleStop();}
}

void Intake::runAutoIndexer(){
  // if(master.get_digital(DIGITAL_L1) == 1){
    double midLightAverage = botLight.get_value(); //+ topLight.get_value())/2;
    double topLightAverage = topLight.get_value();
    if(topLightAverage <=2800){
      indexerStop();
      if(midLightAverage >= 2500){
        middleSpin(50);}
      else{
        middleStop();
       }
     }
    else{
    intakeSpin(600);
    middleSpin(50);
    indexerSpin(50);
  }
  printf("lightAverage  %F \n",midLightAverage);
// }// else if(master.get_digital(DIGITAL_R1) !=1 && master.get_digital(DIGITAL_R2) !=1 && master.get_digital(DIGITAL_Y) !=1 && master.get_digital(DIGITAL_A)){indexerStop(); middleStop();}
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

void Intake::autoSort(int allianceColor){
  switch (allianceColor){
    case REDBALL:{
      optical.set_led_pwm(ledLevel);
      intakeSpinVelocity(600);
      middleSpinVelocity(600);
      indexerSpinVelocity(280);
      double currentHue = optical.get_hue();
      printf("currentHue %F\n", currentHue); //debug code
      if(optical.get_hue() <= 10){ //Sees RED Ball //If there is a ball at the top already it will stop this ball at the Optical Sensor
        middleSpinVelocity(600);
        indexerSpinVelocity(280);
        if(topLight.get_value()<=2800)middleStop();
      }
      if(optical.get_hue() >= 220){middleSpinVelocity(600); if(topLight.get_value() >=2800){indexerSpinVelocity(-600);}} //If there is a blue ball it will send it out back.
      if(topLight.get_value() <=2800){
        indexerStop();
      }
      break;
    }
    case BLUEBALL:{
      optical.set_led_pwm(ledLevel);
      intakeSpinVelocity(600);
      middleSpinVelocity(600);
      indexerSpinVelocity(280);
      double currentHue = optical.get_hue();
      printf("currentHue %F\n", currentHue); //debug code
      if(optical.get_hue() >=220){ //Sees BLUE Ball //If there is a ball at the top already it will stop this ball at the Optical Sensor
        middleSpinVelocity(600);
        indexerSpinVelocity(280);
        if(topLight.get_value()<=2800)middleStop();
      }
      if(optical.get_hue() <=10){middleSpin(600); if(topLight.get_value() >=2800){indexerSpin(-600);}} //If there is a RED ball it will send it out back.
      if(topLight.get_value() <=2800){
        indexerStop();
      }
      break;
    }
  }
}

void Intake::goalSort(int allianceColor){
  switch (allianceColor){
    case REDBALL:{
      optical.set_led_pwm(ledLevel);
      intakeSpin(200);
      middleSpin(600);
      indexerSpin(600);
      double currentHue = optical.get_hue();
      printf("currentHue %F\n", currentHue); //debug code
      if(optical.get_hue() >= 220){indexerSpin(-600);} //If there is a blue ball it will send it out back.
      break;
    }
    case BLUEBALL:{
      optical.set_led_pwm(ledLevel);
      intakeSpin(200);
      middleSpin(600);
      indexerSpin(600);
      double currentHue = optical.get_hue();
      printf("currentHue %F\n", currentHue); //debug code
      if(optical.get_hue() <= 10){indexerSpin(-600);} //If there is a red ball it will send it out back.
      break;
    }
  }
}
