#include "main.h"
#include "class/control/auton.hpp"
#include "class/control/chassis.hpp"
#include "class/control/intakes.hpp"

static Chassis chassis;
static Intake intake;

/*
When Adjusting PD and Slew values use this as a guide for what needs to change.

Not going far enough? Increase kP
Not Smooth second half? Incrase kD
Startup too slow? Increase slew_rate
Isn't settling? Increase kP or broaden exit range
*/

Auton& Auton::run(){
 while(true){
 // blueAutoSortTask.suspend();
 // redAutoSortTask.suspend();
  switch (startPos) { //Where am I? Starting Position
    case 1: {
      switch (firstPos) {
        case 1: { //robot's mvmt from 1 to 1 //
          // chassis.withTurnPD(200000000,.1).withTurnSlew(2).turn(90).waitUntilSettled();
          currentPos = 1; break;}
        case 2: { //robot's mvmt from 1 to 2
          currentPos = 2; break;}
        case 3: {currentPos = 3; }//robot's mvmt from 1 to 3
        case 4: {currentPos = 4; }//robot's mvmt from 1 to 4
        case 5: {currentPos = 5; }//robot's mvmt from 1 to 5
        case 6: {
          chassis.withPD(0.2,0.001).withSlew(2).withHeading(359,1).withDist(40).drive(2700);
          for(int i=0; i<3; i+=1){
            intake.middleSpinVelocity(-600);
            intake.intakeSpinVelocity(-600);
            pros::delay(400);
            intake.middleSpinVelocity(600);
            intake.intakeSpinVelocity(600);
            pros::delay(500);
          }
          intake.intakeSpinVelocity(600);
          intake.middleSpinVelocity(200);
          intake.indexerSpinVelocity(600);
          // LF.move_relative(-50,100);
          // LB.move_relative(-50,100);
          // RF.move_relative(50,100);
          // RB.move_relative(50,100);
          currentPos = 6; }//robot's mvmt from 1 to 6
        default: { startPos=0;break;}
      } }
    case 2: {
      switch (firstPos) {
        case 1: {
          chassis.withPD(0.075,0.001).withSlew(2).withHeading(0,1).drive(-5000);
          currentPos = 1; break;}//robot's mvmt from -1 to 1 //
        case 2: {
          chassis.setState(COAST);
          // intake.iinit();
          intake.indexerSpinVelocity(200);
          pros::delay(200);
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
          chassis.withPD(0.2,0.001).withSlew(2).withHeading(0,1).drive(1500);
          pros::delay(200);
          chassis.withTurnPD(1.5,1).withTurnSlew(1).withTurnDirection(LEFT).turn(283).waitUntilSettled();
          // chassis.withPD(0.22,0.001).withSlew(1).withHeading(270).drive(900);
          chassis.withPD(.5,0.001).withSlew(1).withHeading(283,1).autoSort(1).withDist(35).drive(1000);
          intake.middleSpinVelocity(600);
          intake.indexerSpinVelocity(200);
          pros::delay(400);
          currentPos = 1; break;
        }//robot's mvmt from 2 to 1
        case 3: {//robot's mvmt from 2 to 3
          chassis.withPD(0.075,0.001).withSlew(100).withHeading(0,1).drive(1500);
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
          intake.indexerStop();
          intake.middleStop();
          chassis.withPD(.225,0.001).withSlew(1).withHeading(283,1).autoSort(1).drive(-600);
          pros::delay(200);
          chassis.withTurnPD(1.125,.1).justPD(1).withTurnDirection(LEFT).turn(145).waitUntilSettled();
          chassis.withPD(0.2,0.001).withSlew(2).withHeading(145,1).drive(3500);
          chassis.withTurnPD(1.2,.1).withTurnDirection(RIGHT).justPD(1).turn(185).waitUntilSettled();
          // pros::delay(200);
          chassis.withPD(0.15,0.001).withSlew(2).withHeading(185,1).autoSort(1).withDist(40).drive(1300);
          while(1){
            intake.goalSort(alliance);
            pros::delay(15);
          }
          // intake.intakeSpinVelocity(600);
          // intake.middleSpinVelocity(600);
          // intake.indexerSpinVelocity(200);
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
          chassis.withPD(0.075,0.001).withSlew(100).withHeading(0,1).drive(-1500);
          chassis.withTurnPD(.01,.1).withTurnSlew(2).turn(130).waitUntilSettled();
          chassis.withPD(0.075,0.001).withSlew(100).withHeading(0,1).drive(2500);
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
  intake.iiInit();
  intake.indexerSpinVelocity(200);
  //Goal 1 (G)

  pros::delay(100);
  intake.indexerStop();
  chassis.withPD(0.4,0.001).withSlew(2).withHeading(10,1).autoSort(1).drive(3000);
  chassis.withTurnPD(1.1,1).withTurnSlew(1).withTurnDirection(LEFT).turn(230).waitUntilSettled();
  chassis.withPD(0.35,0.001).withSlew(1).withHeading(230).autoSort(0).withDist(40).drive(1500);
  intake.goalSort(REDBALL, 50);
  intake.indexerSpinVelocity(-200);
  //Goal 2 (D)

  chassis.withPD(0.2,0.001).withSlew(1).withHeading(230).autoSort(1).drive(-350);
  chassis.withTurnPD(1.15,1).withTurnDirection(RIGHT).justPD(1).turn(330).waitUntilSettled();
  chassis.withPD(0.15,1).withSlew(2).withHeading(330).autoSort(1).drive(2000);
  chassis.withTurnPD(1.1,1).withTurnSlew(1).withTurnDirection(LEFT).turn(285).waitUntilSettled();
  chassis.withPD(0.2,1).withSlew(1).withHeading(285).autoSort(0).withDist(40).drive(600);
  intake.goalSort(REDBALL, 50);
  intake.indexerSpinVelocity(-200);
  //Goal 3 (A)

  chassis.withPD(0.2,0.001).withSlew(1).withHeading(270).drive(-425);
  chassis.withTurnPD(.89,0.09).withTurnDirection(RIGHT).justPD(1).turn(90).waitUntilSettled();
  chassis.withPD(0.2,0.001).withSlew(1).withHeading(87).autoSort(1).drive(2400);
  chassis.withTurnPD(.25,1).withTurnSlew(1).withTurnDirection(LEFT).justPD(1).turn(325).waitUntilSettled();
  chassis.withPD(0.2,0.001).withSlew(1).withHeading(325).autoSort(1).withDist(40).drive(1500);
  intake.goalSort(REDBALL, 50);
  intake.indexerSpinVelocity(-200);
  // intake.indexerSpinVelocity(200);
  // Goal 4 (B)

  chassis.withPD(0.2,0.001).withSlew(1).withHeading(300).drive(-300);
  chassis.withTurnPD(.9,1).withTurnSlew(1).withTurnDirection(RIGHT).justPD(1).turn(75).waitUntilSettled();
  chassis.withPD(0.2,0.001).withSlew(1).withHeading(75).autoSort(1).drive(2000);
  chassis.withTurnPD(.35,.1).withTurnSlew(1).withTurnDirection(LEFT).justPD(1).turn(315).waitUntilSettled();
  chassis.withPD(1,0.001).withSlew(1).withHeading(315).autoSort(1).drive(1000);
  chassis.withTurnPD(.4,.1).withTurnSlew(1).withTurnDirection(RIGHT).justPD(1).turn(0).waitUntilSettled();
  chassis.withPD(0.2,0.001).withSlew(1).withHeading(0).withDist(50).drive(1500);
  intake.goalSort(REDBALL, 50);
  intake.indexerSpinVelocity(-200);
  // Goal 5 (C)

  chassis.withPD(0.2,0.001).withSlew(1).withHeading(0).drive(-1300);
  chassis.withTurnPD(.4,.1).withTurnSlew(1).withTurnDirection(RIGHT).justPD(1).turn(155).waitUntilSettled();
  chassis.withPD(0.4,0.001).withSlew(1).withHeading(155).autoSort(1).drive(1500);
  /*
  chassis.withTurnPD(1,1).withTurnSlew(1).withTurnDirection(LEFT).justPD(1).turn(45).waitUntilSettled();
  chassis.withPD(0.4,0.001).withSlew(1).withHeading(45).withDist(50).drive(400);
  intake.indexerSpinVelocity(200);
  //Goal 6 (F)

  chassis.withPD(0.4,0.001).withSlew(1).withHeading(45).drive(-400);
  chassis.withTurnPD(1,1).withTurnSlew(1).withTurnDirection(RIGHT).justPD(1).turn(135).waitUntilSettled();
  chassis.withPD(0.133,0.001).withSlew(1).withHeading(135).autoSort(1).drive(3000);
  chassis.withTurnPD(1,1).withTurnSlew(1).withTurnDirection(LEFT).justPD(1).turn(90).waitUntilSettled();
  chassis.withPD(0.2,0.001).withSlew(1).withHeading(90).drive(200);
  intake.indexerSpinVelocity(200);
  //Goal 7 (I)

  chassis.withPD(0.2,0.001).withSlew(1).withHeading(90).drive(-2000);
  chassis.withTurnPD(1,1).withTurnSlew(1).withTurnDirection(RIGHT).justPD(1).turn(225).waitUntilSettled();
  chassis.withPD(0.133,0.001).withSlew(1).withHeading(225).autoSort(1).drive(2000);
  chassis.withTurnPD(1,1).withTurnSlew(1).withTurnDirection(LEFT).justPD(1).turn(135).waitUntilSettled();
  chassis.withPD(0.4,0.001).withSlew(1).withHeading(135).drive(1000);
  intake.indexerSpinVelocity(200);
  //Goal 8 (H)

  chassis.withPD(0.4,0.001).withSlew(1).withHeading(135).drive(-1000);
  chassis.withTurnPD(1,1).withTurnSlew(1).withTurnDirection(LEFT).justPD(1).turn(315).waitUntilSettled();
  chassis.withPD(0.4,0.001).withSlew(1).withHeading(315).autoSort(1).drive(2000);
  intake.indexerSpinVelocity(200);
  //Goal 9 (E)
*/

  return *this;
}
