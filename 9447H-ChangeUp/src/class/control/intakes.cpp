#include "globals.hpp"
#include "class/control/intakes.hpp"

int Intake::ledLevel = 10, Intake::redHue = 20, Intake::blueHue = 200, Intake::ballsLeft = 0;
bool Intake::oneBall = 0, Intake::pos1 = 0, Intake::pos2 = 0, Intake::stopped = 1, Intake::ball = 0;

void Intake::intakeSpin(int speed){
  leftIntake.move_voltage(speed);
  rightIntake.move_voltage(speed);
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
  leftIntake.move_voltage(0);
  rightIntake.move_voltage(0);
}

void Intake::indexerSpin(int speed){
  indexer.move_voltage(speed);
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
  indexer.move_voltage(0);
}

void Intake::middleSpin(int speed){
  middleIntake.move_voltage(speed);
}

void Intake::middleSpin(int ecount, int speed){
  middleIntake.move_relative(ecount, speed);
}

void Intake::middleSpinVelocity(int velocity){
  middleIntake.move_velocity(velocity);
}

void Intake::middleStop(){
  middleIntake.move_voltage(0);
}

void Intake::runIntakes(){ // Runs the intakes from inputs of R1,R2,L1,L2 on both partner and master controller..
  if(master.get_digital(DIGITAL_L1)){
    intakeSpin(12000);
  }else if(master.get_digital(DIGITAL_L2)){
    intakeSpin(-12000);
  }else{
    intakeStop();
  }
  if(master.get_digital(DIGITAL_R1)){
    indexerSpin(12000);
    middleSpin(12000);
  }else if(master.get_digital(DIGITAL_R2)){
      indexerSpin(-12000);
      middleSpin(-12000);
  } else{
    indexerStop();
    middleStop();
  }

  // if(master.get_digital_new_press(DIGITAL_L1)) ballsLeft++;
  // if(master.get_digital_new_press(DIGITAL_L2)) ballsLeft = 0;
  // if(master.get_digital(DIGITAL_R2)){ intakeSpin(12000);}
  // else if(master.get_digital(DIGITAL_L1)){
  //   autoSort();
  // }
  // if(master.get_digital(DIGITAL_R1)) {
  //   middleSpin(12000); indexerSpin(12000);
  //   // goalSort(alliance); // if(goalDist.get() <= 60 && goalDist.get() != 0{
  // } else if(master.get_digital(DIGITAL_L2)){
  //   intakeSpin(-12000); middleSpin(-12000); indexerSpin(-12000);
  // }
  // if(!master.get_digital(DIGITAL_R2) && !master.get_digital(DIGITAL_L1) && !master.get_digital(DIGITAL_L2)){
  //   intakeStop();
  // }if(!master.get_digital(DIGITAL_R1) && !master.get_digital(DIGITAL_L1) && !master.get_digital(DIGITAL_L2)){
  //   middleStop();
  //   indexerStop();
  //   // autoSort(alliance);
  //   stopped = 1;
  //   ball = 0;
  // }
  // if(master.get_digital(DIGITAL_R1)) {goalSort(alliance);}
  // else if (master.get_digital(DIGITAL_L1)){ indexerSpin(12000); middleStop(); intakeStop();}
  // else if (master.get_digital(DIGITAL_L2)){ intakeSpin(12000); middleSpin(12000); indexerStop(); }
  // else { intakeStop(); middleStop(); indexerStop();}

}

void Intake::iiInit(){
  topOptical.set_led_pwm(ledLevel);
  botOptical.set_led_pwm(ledLevel);
  // leftIntake.set_brake_mode(MOTOR_BRAKE_BRAKE);
  // middleIntake.set_brake_mode(MOTOR_BRAKE_BRAKE);
  // rightIntake.set_brake_mode(MOTOR_BRAKE_BRAKE);
  // indexer.set_brake_mode(MOTOR_BRAKE_BRAKE);
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
  indexerSpin(12000);
  middleSpin(12000);
  intakeSpin(-12000);
  pros::delay(100);
  indexerStop();
  middleStop();
  intakeStop();
}

Intake& Intake::justOneBall(bool oneBall_){
  oneBall = oneBall_;
  if(!oneBall){ ballsLeft = 2;}
  else{ballsLeft = 1;}
  return *this;
}

void Intake::autoSort(int allianceColor){
  switch (allianceColor){
    case REDBALL:{
      intakeSpin(8000);
      if( ballIndexer.get() <= 100 && ballIndexer.get() != 0 ){ middleStop(); indexerStop(); pos1 = 1; }
      else { middleSpin(3500); indexerSpin(3500); pos1 = 0; }
      if(pos1 && botOptical.get_hue() <= redHue) {
        indexerSpin(6000); middleSpin(6000);
        if( topOptical.get_hue() <= redHue ) { indexerStop(); middleStop(); }
      }

      printf("TopOptical: %F BotOptical: %F\n", topOptical.get_hue(), botOptical.get_hue()); //debug code

      pros::delay(15);
      break;
    }
    case BLUEBALL:{
      intakeSpin(8000);
      if( ballIndexer.get() <= 100 && ballIndexer.get() != 0 ){ middleStop(); indexerStop(); pos1 = 1; }
      else { middleSpin(3500); indexerSpin(3500); pos1 = 0; }
      if(pos1 && botOptical.get_hue() <= redHue) {
        indexerSpin(6000); middleSpin(6000);
        if( topOptical.get_hue() <= redHue ) { indexerStop(); middleStop(); }
      }

      printf("TopOptical: %F BotOptical: %F\n", topOptical.get_hue(), botOptical.get_hue()); //debug code

      pros::delay(15);
      break;
    }
  }
}

void Intake::goalSort(int allianceColor){
  switch (allianceColor){
    case REDBALL:{
      if(stopped){
        intakeSpin(12000);
        middleSpin(12000);
        indexerSpin(12000);
        stopped = 0;
      }
      if(botOptical.get_hue() >= blueHue && botOptical.get_proximity() >= 240 && botOptical.get_hue() <= 300){
        middleSpin(8000); indexerSpin(8000);
        ball = 1;
      }

      if(ball) { if(topOptical.get_hue() >= blueHue && topOptical.get_proximity() >= 150 && topOptical.get_hue() <= 300) { middleStop(); indexerStop(); intakeSpin(-12000); } }

      pros::delay(1);
      break;
    }
    case BLUEBALL:{
      if(ballsLeft > 0)intakeSpin(12000);
      if(ballsLeft == 0)intakeSpin(-12000);
      indexerSpin(12000);
      if(!oneBall)middleSpin(12000);

      if(topOptical.get_hue() <= redHue){indexerStop(); ballsLeft-=1;}
      if(ballsLeft == 1){ //Only stop balls at the bottom if only needs to take one ball or if the top is already stopped.
        if(botOptical.get_hue() >= redHue){middleStop(); intakeSpin(-12000); ballsLeft -=1;}
      }

      printf("TopOptical: %F BotOptical: %F\n", topOptical.get_hue(), botOptical.get_hue()); //debug code
      break;
    }
  }
}

void Intake::goalSort(int allianceColor, int time, bool state){
  if(state==1){
    for(int i=0; i<time;i++){
      goalSort(allianceColor);
      pros::delay(15);
    }
  }
  intakeStop();
  middleStop();
  indexerStop();
  oneBall = 0;
  ballsLeft = 0;
}

void Intake::dropBall(){
  intakeSpin(-12000);
  middleSpin(-12000);
  indexerSpin(-12000);
}

void Intake::calibrate(int resting_value){
  for(int i=0; botOptical.get_hue() < resting_value+5 && botOptical.get_hue() > resting_value-5; i++){botOptical.set_led_pwm(i);}
  for(int i=0; topOptical.get_hue() < resting_value+5 && topOptical.get_hue() > resting_value-5; i++){topOptical.set_led_pwm(i);}
}
