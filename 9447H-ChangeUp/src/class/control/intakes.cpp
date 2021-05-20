#include "globals.hpp"
#include "class/control/intakes.hpp"

int Intake::ledLevel = 10, Intake::redHue = 20, Intake::blueHue = 200, Intake::ballsLeft = 0;
bool Intake::oneBall = 0, Intake::pos1 = 0, Intake::pos2 = 0, Intake::stopped = 1, Intake::ball = 0, Intake::twoBalls = 0;

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
  stopped = 1;
  ball = 0;
}

void Intake::rollerSpin(int speed){
  indexer.move_voltage(speed);
  middleIntake.move_voltage(speed);
}

void Intake::rollerStop(){
  indexer.move_voltage(0);
  middleIntake.move_voltage(0);
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
  // if(master.get_digital(DIGITAL_L2)){
  //   ball
  // }

  while(1){
  if(master.get_digital(DIGITAL_L1)){
    // intakeSpin(12000);
    if(master.get_digital(DIGITAL_R1)){
      intakeSpin(12000);}
      else{autoSort();}
    if(!master.get_digital(DIGITAL_R1) && !master.get_digital(DIGITAL_R2)){
    rollerSpin(500);
    }
  }else if(master.get_digital(DIGITAL_L2)){
    intakeSpin(-12000);
  }else{
    intakeStop();
    stopped = 1;
  }
  if(master.get_digital(DIGITAL_R1)){
    rollerSpin(12000);
  }else if(master.get_digital(DIGITAL_R2)){
    rollerSpin(-12000);
  }
  if( !master.get_digital(DIGITAL_R1) && !master.get_digital(DIGITAL_L1) && !master.get_digital(DIGITAL_R2)){
    rollerStop();
  }
}
  // while(1){
  // if(master.get_digital(DIGITAL_L1)){
  //   autoSort();
  // }else if(master.get_digital(DIGITAL_R1)){
  //   // intakeSpin(12000);
  //   // rollerSpin(12000);
  //   // pros::delay(150);
  //   goalSort(alliance);
  // }
  // else{
  //   intakeStop();
  //   rollerStop();
  //   stopped = 1;
  //   ball = 0;
  // }
  // pros::delay(5);
  // }
}

void Intake::iiInit(){
  topOptical.set_led_pwm(ledLevel);
  botOptical.set_led_pwm(ledLevel);
  leftIntake.tare_position();
  rightIntake.tare_position();
  middleIntake.tare_position();
  indexer.tare_position();
  intakeLock();
}

void Intake::intakeLock(){
  leftIntake.set_brake_mode(MOTOR_BRAKE_BRAKE);
  middleIntake.set_brake_mode(MOTOR_BRAKE_BRAKE);
  rightIntake.set_brake_mode(MOTOR_BRAKE_BRAKE);
  indexer.set_brake_mode(MOTOR_BRAKE_BRAKE);
}

void Intake::deploy(){
  iiInit();
  rollerSpin(12000);
  intakeSpin(-12000);
  pros::delay(100);
  rollerStop();
  intakeStop();
}

Intake& Intake::twoBall(bool twoBall_){
  twoBalls = twoBall_;
  return *this;
}

void Intake::autoSort(int allianceColor){
  switch (allianceColor){
    case REDBALL:{
      intakeSpin(12000);
      rollerSpin(9000);
      if(topOptical.get_proximity() >= 50){
        rollerStop();
        // if(botOptical.get_proximity() >= 50){
        //   intakeStop();
        // }
      }
      printf("TopOptical: %F BotOptical: %F\n", topOptical.get_hue(), botOptical.get_hue()); //debug code
      pros::delay(15);
      break;
    }
    case BLUEBALL:{
      intakeSpin(12000);
      rollerSpin(10000);
      if(topOptical.get_proximity() >= 30){
        rollerStop();
        if(botOptical.get_proximity() >= 30){
          intakeStop();
        }
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
      if(ball){rollerStop(); intakeSpin(-120000); break;}
      if(stopped){
        rollerSpin(12000);
        pros::delay(500);
        intakeSpin(12000);
        if(twoBalls){rollerSpin(6000);}
        stopped = 0;
      }
      if(twoBalls){
        if(topOptical.get_hue() >= blueHue){
          rollerStop();
          intakeSpin(-12000);
          ball = 1;
        }
      }else if(botOptical.get_hue() >=  blueHue){
        intakeSpin(-120000);
        rollerStop();
        ball = 1;
      }
      printf("TopOptical: %F BotOptical: %F\n", topOptical.get_hue(), botOptical.get_hue()); //debug code
      pros::delay(15);
      break;
    }
    case BLUEBALL:{
      intakeSpin(12000);
      rollerSpin(9000);
      if(topOptical.get_hue() <= redHue){
        rollerStop();
        // if(botOptical.get_proximity() >= 50){
        //   intakeStop();
        // }
      }
      printf("TopOptical: %F BotOptical: %F\n", topOptical.get_hue(), botOptical.get_hue()); //debug code
      pros::delay(15);
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
  rollerStop();
  oneBall = 0;
  ballsLeft = 0;
}

void Intake::dropBall(){
  intakeSpin(-12000);
  rollerSpin(-12000);
}

void Intake::calibrate(int resting_value){
  for(int i=0; botOptical.get_hue() < resting_value+5 && botOptical.get_hue() > resting_value-5; i++){botOptical.set_led_pwm(i);}
  for(int i=0; topOptical.get_hue() < resting_value+5 && topOptical.get_hue() > resting_value-5; i++){topOptical.set_led_pwm(i);}
}
