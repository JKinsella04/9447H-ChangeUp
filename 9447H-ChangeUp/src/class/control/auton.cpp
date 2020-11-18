#include "main.h"

#include "class/control/auton.h"
#include "class/control/chassis.h"
#include "class/control/intakes.h"

static Chassis chassis;
static Intake intake;

Auton& Auton::run(){
 while(true){
  switch (startPos) { //Where am I? Starting Position
    case 1: {
      switch (firstPos) {
        case 1: { //robot's mvmt from 1 to 1 //
          // chassis.withTurnPD(200000000,.1).withTurnSlew(2).turn(90).waitUntilSettled();
          currentPos = 1; break;}
        case 2: { //robot's mvmt from 1 to 2
          // chassis.withPD(0.075,0.001).withSlew(2).withHeading(0).drive(-100);
          LF.move_relative(100, 200);
          LB.move_relative(100, 200);
          RF.move_relative(-100, 200);
          RB.move_relative(-100, 200);
          intake.indexerSpinVelocity(600);
          pros::delay(1000);
          intake.indexerStop();
          currentPos = 2; firstPos=0; break;}
        case 3: {currentPos = 3; }//robot's mvmt from 1 to 3
        case 4: {currentPos = 4; }//robot's mvmt from 1 to 4
        case 5: {currentPos = 5; }//robot's mvmt from 1 to 5
        case 6: {currentPos = 6; }//robot's mvmt from 1 to 6
        default: { startPos=0;break;}
      } }
    case 2: {
      switch (firstPos) {
        case 1: {
          chassis.withPD(0.075,0.001).withSlew(2).withHeading(0).drive(-5000);
          currentPos = 1; break;}//robot's mvmt from -1 to 1 //
        case 2: {
          chassis.setState(HOLD);
          intake.indexerSpinVelocity(200);
          pros::delay(100);
          intake.indexerStop();
          currentPos = 2; break; }//robot's mvmt from -1 to 2
        case 3: {currentPos = 3; }//robot's mvmt from -1 to 3
        case 4: {currentPos = 4; }//robot's mvmt from -1 to 4
        case 5: {currentPos = 5; }//robot's mvmt from -1 to 5
        case 6: {currentPos = 6; }//robot's mvmt from -1 to 6
      }startPos=0;}
    default:{break;}
  } //switch
  switch (currentPos){ //Where am I? First Position
    case 1: {
      switch (secondPos) {
        case 2: {currentPos = 2;}//robot's mvmt from 1 to 2
        case 3: {currentPos = 3;}//robot's mvmt from 1 to 3
        case 4: {currentPos = 4;}//robot's mvmt from 1 to 4
        case 5: {
            // chassis.withTurnPD(2,.1).withTurnSlew(2).turn(90).waitUntilSettled();
            currentPos = 5;}//robot's mvmt from 1 to 5
        case 6: {currentPos = 6;}//robot's mvmt from 1 to 6
      }break;}
    case 2: {
      switch (secondPos) {
        case 1: {
          chassis.withPD(0.075,0.001).withSlew(50).withHeading(0).drive(1000);
          pros::delay(200);
          chassis.withTurnPD(1.52,.8).withTurnSlew(.15).withTurnDirection(LEFT).turn(275).waitUntilSettled();
          // pros::delay(200);
          intake.intakeSpinVelocity(200);
          intake.middleSpinVelocity(600);
          intake.indexerSpinVelocity(200);
          chassis.withPD(0.075,0.001).withSlew(100).withHeading(0).drive(750);
          currentPos = 1; break;
        }//robot's mvmt from 2 to 1
        case 3: {//robot's mvmt from 2 to 3
          chassis.withPD(0.075,0.001).withSlew(100).withHeading(0).drive(1500);
          chassis.withTurnPD(1,.1).withTurnSlew(1).withTurnDirection(RIGHT).turn(135).waitUntilSettled();

          currentPos = 3; break;}
        case 4: {currentPos = 4;}//robot's mvmt from 2 to 4
        case 5: {currentPos = 5;}//robot's mvmt from 2 to 5
        case 6: {currentPos = 6;}//robot's mvmt from 2 to 6
      }break;}
    case 3: {
      switch (secondPos) {
        case 1: {currentPos = 1;}//robot's mvmt from 3 to 1
        case 2: {currentPos = 2;}//robot's mvmt from 3 to 2
        case 4: {currentPos = 4;}//robot's mvmt from 3 to 4
        case 5: {currentPos = 5;}//robot's mvmt from 3 to 5
        case 6: {currentPos = 6;}//robot's mvmt from 3 to 6
      }break;}
    case 4: {
      switch (secondPos) {
        case 1: {currentPos = 1;}//robot's mvmt from 4 to 1
        case 2: {currentPos = 2;}//robot's mvmt from 4 to 2
        case 3: {currentPos = 3;}//robot's mvmt from 4 to 3
        case 5: {currentPos = 5;}//robot's mvmt from 4 to 5
        case 6: {currentPos = 6;}//robot's mvmt from 4 to 6
      }break;}
    case 5: {
      switch (secondPos) {
        case 1: {currentPos = 1;}//robot's mvmt from 5 to 1
        case 2: {currentPos = 2;}//robot's mvmt from 5 to 2
        case 3: {currentPos = 3;}//robot's mvmt from 5 to 3
        case 4: {currentPos = 4;}//robot's mvmt from 5 to 4
        case 6: {currentPos = 6;}//robot's mvmt from 5 to 6
      }break;}
    case 6: {
      switch (secondPos) {
        case 1: {currentPos = 1;}//robot's mvmt from 6 to 1
        case 2: {currentPos = 2;}//robot's mvmt from 6 to 2
        case 3: {currentPos = 3;}//robot's mvmt from 6 to 3
        case 4: {currentPos = 4;}//robot's mvmt from 6 to 4
        case 5: {currentPos = 5;}//robot's mvmt from 6 to 5
      }break;} //case 6

  } //switch
  switch (currentPos){ //Where am I? Second Position
    case 1: {
      switch (thirdPos) {
        case 2: {currentPos = 2;}//robot's mvmt from 1 to 2
        case 3: {
          chassis.withPD(0.075,0.001).withSlew(50).withHeading(0).drive(-1000);
          pros::delay(200);
          chassis.withTurnPD(1.52,.8).withTurnSlew(.15).withTurnDirection(LEFT).turn(135).waitUntilSettled();
          currentPos = 3; break;
        }//robot's mvmt from 1 to 3
        case 4: {currentPos = 4;}//robot's mvmt from 1 to 4
        case 5: {currentPos = 5;}//robot's mvmt from 1 to 5
        case 6: {currentPos = 6;}//robot's mvmt from 1 to 6
      }}
    case 2: {
      switch (thirdPos) {
        case 1: {currentPos = 1;}//robot's mvmt from 2 to 1
        case 3: {currentPos = 3;}//robot's mvmt from 2 to 3
        case 4: {currentPos = 4;}//robot's mvmt from 2 to 4
        case 5: {currentPos = 5;}//robot's mvmt from 2 to 5
        case 6: {currentPos = 6;}//robot's mvmt from 2 to 6
      }}
    case 3: {
      switch (thirdPos) {
        case 1: {
          chassis.withPD(0.075,0.001).withSlew(100).withHeading(0).drive(-1000);
          chassis.withTurnPD(.01,.1).withTurnSlew(2).turn(270).waitUntilSettled();
          currentPos = 1;}//robot's mvmt from 3 to 1
        case 2: {currentPos = 2;}//robot's mvmt from 3 to 2
        case 4: {currentPos = 4;}//robot's mvmt from 3 to 4
        case 5: {currentPos = 5;}//robot's mvmt from 3 to 5
        case 6: {currentPos = 6;}//robot's mvmt from 3 to 6
      }}
    case 4: {
      switch (thirdPos) {
        case 1: {currentPos = 1;}//robot's mvmt from 4 to 1
        case 2: {currentPos = 2;}//robot's mvmt from 4 to 2
        case 3: {currentPos = 3;}//robot's mvmt from 4 to 3
        case 5: {currentPos = 5;}//robot's mvmt from 4 to 5
        case 6: {currentPos = 6;}//robot's mvmt from 4 to 6
      }}
    case 5: {
      switch (thirdPos) {
        case 1: {currentPos = 1;}//robot's mvmt from 5 to 1
        case 2: {currentPos = 2;}//robot's mvmt from 5 to 2
        case 3: {currentPos = 3;}//robot's mvmt from 5 to 3
        case 4: {currentPos = 4;}//robot's mvmt from 5 to 4
        case 6: {currentPos = 6;}//robot's mvmt from 5 to 6
      }}
    case 6: {
      switch (thirdPos) {
        case 1: {currentPos = 1;}//robot's mvmt from 6 to 1
        case 2: {currentPos = 2;}//robot's mvmt from 6 to 2
        case 3: {currentPos = 3;}//robot's mvmt from 6 to 3
        case 4: {currentPos = 4;}//robot's mvmt from 6 to 4
        case 5: {currentPos = 5;}//robot's mvmt from 6 to 5
      }} //case 6

  }
pros::delay(20);} //while
  return *this;
}

Auton& Auton::runSkills(){
  intake.indexerSpinVelocity(200);
  chassis.withPD(0.15,1).withSlew(2).withHeading(0).drive(1500);
  chassis.withTurnPD(2,.15).withTurnSlew(2).withTurnDirection(RIGHT).turn(135).waitUntilSettled();
  // intake.deploy();
  // LF.move_relative(1, 200);
  // LB.move_relative(1, 200);
  // RF.move_relative(1, 200);
  // RB.move_relative(1, 200);
  // chassis.withTurnPD(2,.15).withTurnSlew(2).withTurnDirection(RIGHT).turn(50).waitUntilSettled();
  // intake.intakeSpin(600);
  // chassis.withPD(0.15,1).withSlew(2).withHeading(0).drive(1050);
  // chassis.withTurnPD(1.2,.11).withTurnSlew(2).withTurnDirection(RIGHT).turn(135).waitUntilSettled();
  // chassis.withPD(0.15,1).withSlew(2).withHeading(0).drive(700);
  // intake.middleSpin(600);
  // intake.indexerSpin(600);
  // pros::delay(50);
  // intake.indexerSpin(-600);
  // pros::delay(10);
  // intake.indexerSpin(600);
  // intake.intakeSpin(600);
  // pros::delay(500);
  // intake.intakeStop(); intake.middleStop(); intake.indexerStop();
  // chassis.withPD(0.15,1).withSlew(2).withHeading(0).drive(-1000); //back up
  // chassis.withTurnPD(2,.1).withTurnSlew(2).withTurnDirection(RIGHT).turn(90).waitUntilSettled();//turn left
  // intake.intakeSpin(600);
  // chassis.withPD(0.15,1).withSlew(2).withHeading(0).drive(750);
  // intake.indexerSpin(600);
  // chassis.withTurnPD(.9,.1).withTurnSlew(2).withTurnDirection(RIGHT).turn(225).waitUntilSettled();
  //turn right to goal
  //go forward
  //deposit
  //back up
  //turn right to 270
  //go forward and pick up ball
  //turn left
  return *this;
}
