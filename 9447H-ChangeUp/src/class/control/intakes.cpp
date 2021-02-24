#include "globals.hpp"
#include "class/control/intakes.hpp"

int Intake::ledLevel = 75, Intake::doubleShotDelay = 100, Intake::redHue = 20, Intake::blueHue = 200, Intake::ballsLeft = 0;
bool Intake::full=0, Intake::ball=0, Intake::holdComplete=0, Intake::oneBall=0;
double Intake::currentHue = 40, Intake::opticalAverage = 40; //greenish value robot never checks for this color so it is a "safe" value.

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

void Intake::runIntakes(){ // Runs the intakes from inputs of R1,R2,L1,L2 on both partner and master controller..
  printf("ballsLeft %d\n", ballsLeft);
  partner.print(2, 0, "Balls Left: %d", ballsLeft);
  if(LOptical.get_proximity() < 254){currentHue=40; opticalAverage = 40;}
  if(ballsLeft < 0)ballsLeft=0;
  if(partner.get_digital(DIGITAL_R2)){runAutoIndexer();}
  else if(partner.get_digital(DIGITAL_L2)){justOneBall(1);runAutoIndexer();}
  else{holdComplete=0; oneBall=0; ball=0;}
  if(partner.get_digital_new_press(DIGITAL_L1)){ballsLeft++;}
  else if(partner.get_digital(DIGITAL_R1)){ballsLeft=0; partner.clear_line(2);}
  if(partner.get_digital(DIGITAL_R2) == 0){
    if(master.get_digital(DIGITAL_R2) || partner.get_digital(DIGITAL_A)){intakeSpin(-600); middleSpin(-600); indexerSpin(-200);}
    else {
      if(master.get_digital(DIGITAL_R1)){
        if(goalDist.get() < 50 && goalDist.get() != 0 )goalSort(alliance);
        if(ballsLeft >=1)intakeSpinVelocity(600);
        else{intakeSpinVelocity(-600);}
      }else {
        autoSort(alliance);
      }
    }
  }
}

void Intake::runAutoIndexer(){
  switch(alliance){
    case 2:{ //Blue Alliance
      if(!holdComplete){
        double opticalAverage = (LOptical.get_hue() + ROptical.get_hue())/2;
        if(opticalAverage <= redHue){
          ball = 1;
          middleSpinVelocity(200);
          indexerSpinVelocity(100);
          if(oneBall==1){intakeStop(); middleStop();holdComplete=1; break;}
        }
        if(ballIndexer.get() <= 50 && ballIndexer.get() !=0 && ball){
          indexerStop();
          if(opticalAverage <= redHue){
            middleStop();
            intakeStop();
            holdComplete =1;
          }
        }
        if(ball == 0){
          intakeSpinVelocity(600);
          middleSpinVelocity(600);
          indexerSpinVelocity(200);
        }
        printf("lightAverage, blueBall  %d %d\n",topLight.get_value(), ball);
      }
    // intakeStop();
    // middleStop();
    // indexerStop();
    break;}
    default:{ //Red Alliance and Skills
      if(!holdComplete){
        if(LOptical.get_proximity() >= 254) opticalAverage = (LOptical.get_hue() + ROptical.get_hue())/2;
        if(opticalAverage >= blueHue){
          ball = 1;
          if(oneBall==1){intakeStop(); middleStop();holdComplete=1; break;}
          else{middleSpinVelocity(200); indexerSpinVelocity(100);}
        }
        if(ballIndexer.get() <=50 && ballIndexer.get() !=0 && ball == 1){
          indexerStop();
          if(opticalAverage >= blueHue){
            middleStop();
            intakeStop();
            holdComplete =1;
          }
        }
        if(ball == 0){
          intakeSpinVelocity(600);
          middleSpinVelocity(600);
          indexerSpinVelocity(200);
        }
        // printf("opticalAverage, holdComplete  %d %b\n", opticalAverage, holdComplete);
      }
    // intakeStop();
    // middleStop();
    // indexerStop();
    break;}
  }

}

void Intake::iiInit(){
  LOptical.set_led_pwm(ledLevel);
  ROptical.set_led_pwm(ledLevel);
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
  indexerSpinVelocity(200);
  intakeSpinVelocity(-600);
  pros::delay(100);
  intakeSpinVelocity(600);
}

Intake& Intake::justOneBall(bool oneBall_){
  oneBall = oneBall_;
  return *this;
}

void Intake::autoSort(int allianceColor){
  switch (allianceColor){
    case REDBALL:{
      full=0;
      intakeSpinVelocity(600);
      indexerSpinVelocity(100);
      if(ballIndexer.get() <=50 && ballIndexer.get() !=0){
        full=1;
        indexerStop();
      }
      if(LOptical.get_proximity() >= 254)currentHue = (LOptical.get_hue() + ROptical.get_hue())/2;
      printf("currentHue %F\n", currentHue); //debug code
      if(currentHue <= redHue && full==1){ //Sees RED Ball //If there is a ball at the top already it will stop this ball at the Optical Sensor
        middleStop();
      }else{middleSpinVelocity(300);}
      if(currentHue >= blueHue){middleSpinVelocity(600); if(ballIndexer.get() >= 50 || ballIndexer.get() == 0){indexerSpinVelocity(-200);}pros::delay(15);} //If there is a blue ball it will send it out back.
      break;
    }
    case BLUEBALL:{
      full=0;
      intakeSpinVelocity(600);
      indexerSpinVelocity(100);
      if(ballIndexer.get() <=50 && ballIndexer.get() !=0){
        full=1;
        indexerStop();
      }
      if(LOptical.get_proximity() >= 254)currentHue = (LOptical.get_hue() + ROptical.get_hue())/2;
      printf("currentHue %F\n", currentHue); //debug code
      if(currentHue >= blueHue && full==1){ //Sees BLUE Ball //If there is a ball at the top already it will stop this ball at the Optical Sensor
        middleStop();
      }else{middleSpinVelocity(300);}
      if(currentHue <= redHue){middleSpinVelocity(600); if(ballIndexer.get() >=50 || ballIndexer.get() ==0){indexerSpinVelocity(-200);}pros::delay(15);} //If there is a RED ball it will send it out back.
      break;
    }
  }
}

void Intake::goalSort(int allianceColor){
  switch (allianceColor){
    case REDBALL:{
      if(ballsLeft > 0)intakeSpin(200);
      if(ballsLeft == 0)intakeSpin(-600);
      indexerSpin(200);
      middleSpin(600);
      if(LOptical.get_proximity() >= 50)currentHue = (LOptical.get_hue() + ROptical.get_hue())/2;
      printf("currentHue %F\n", currentHue); //debug code
      if(currentHue >= blueHue){ballsLeft-=1; partner.rumble("."); if(ballsLeft==0){intakeSpin(-600);} indexerSpin(-200);pros::delay(400);} //If there is a blue ball it will send it out back.
      break;
    }
    case BLUEBALL:{
      if(ballsLeft > 0)intakeSpin(200);
      if(ballsLeft == 0)intakeSpin(-600);
      indexerSpin(200);
      middleSpin(600);
      if(LOptical.get_proximity() >= 50)currentHue = (LOptical.get_hue() + ROptical.get_hue())/2;
      printf("currentHue %F\n", currentHue); //debug code
      if(currentHue <= redHue){ballsLeft-=1; partner.rumble("."); if(ballsLeft==0){intakeSpin(-600);} indexerSpin(-200);pros::delay(400);} //If there is a red ball it will send it out back.
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
  }else{
    indexerSpinVelocity(200);
    middleSpinVelocity(600);
    pros::delay(100);
    for(int i=0; i<time;i++){
      runAutoIndexer();
      pros::delay(15);
    }
  }
  intakeStop();
  middleStop();
  indexerStop();
  oneBall = 0;
  ball = 0;
  holdComplete =0;
}

void Intake::dropBall(int drop_Mode){
  switch(drop_Mode){
    case REVERSE:{
      intakeSpinVelocity(-100);
      middleSpinVelocity(-200);
      indexerSpinVelocity(-100);
    }
    case EJECT:{
      indexerSpinVelocity(-200);
      pros::delay(450);
      middleSpinVelocity(600);
      break;}
  }
}

void Intake::goalSort(){
  full=0;
  indexerSpinVelocity(200);
  middleSpinVelocity(600);
  pros::delay(600);
  indexerSpinVelocity(100);
  middleSpinVelocity(300);
  while(!full){
    int opticalAverage = (LOptical.get_hue() + ROptical.get_hue())/2;
    intakeSpinVelocity(600);
    if(ballIndexer.get() <=50 && ballIndexer.get() !=0)indexerStop();
    switch(alliance){
      case 1:{ //Red Alliance + Skills
        if(opticalAverage >= blueHue){ middleStop(); intakeStop(); full=1;}
      }
      case 2:{ //Blue Alliance
        if(opticalAverage <= redHue){ middleStop(); intakeStop(); full=1; break;}
      }
    }
  }
}

void Intake::calibrate(int resting_value){
  for(int i=0; LOptical.get_hue() < resting_value+5 && LOptical.get_hue() > resting_value-5; i++){LOptical.set_led_pwm(i);}
  for(int i=0; ROptical.get_hue() < resting_value+5 && ROptical.get_hue() > resting_value-5; i++){ROptical.set_led_pwm(i);}
}
