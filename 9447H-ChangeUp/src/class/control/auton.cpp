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
        case 3: {
          chassis.withPD(0.5,0.001).withSlew(2).withHeading(0,1).autoSort(1).withTol(10).drive(350);
          chassis.withTurnPD(1.2,.1).justPD(1).withTurnDirection(RIGHT).withTol(1).turn(130).waitUntilSettled();
          chassis.withPD(.7,0.001).withSlew(3).withHeading(123,1).autoSort(1).withDist(50).withTol(50).drive(500);
          intake.goalSort();
          currentPos = 3; break; }//robot's mvmt from 1 to 3
        case 4: {currentPos = 4; }//robot's mvmt from 1 to 4
        case 5: {currentPos = 5; }//robot's mvmt from 1 to 5
        case 6: {
          chassis.setState(HOLD);
          chassis.withPD(.35,0.001).withSlew(200).withHeading(3,1).autoSort(1).withTol(10).withDist(35).drive(1500);
          intake.goalSort(alliance, 100, SHOOTBALL);
          currentPos = 6; }//robot's mvmt from 1 to 6
        default: { startPos=0;break;}
      } }
    case 2: {
      switch (firstPos) {
        case 1: {
          chassis.withPD(0.075,0.001).withSlew(2).withHeading(0,1).drive(-5000);
          currentPos = 1; break;}//robot's mvmt from -1 to 1 //
        case 2: {
          chassis.setState(HOLD);
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
          chassis.withPD(0.6,0.001).withSlew(150).withHeading(0,1).withTol(10).drive(1100);
          pros::delay(200);
          chassis.withTurnPD(1.56,1).withTurnSlew(1).withTurnDirection(LEFT).withTol(1).turn(280).waitUntilSettled();
          // chassis.withPD(0.22,0.001).withSlew(1).withHeading(270).drive(900);
          chassis.withPD(.5,0.001).withSlew(125).withHeading(280,1).autoSort(1).withDist(50).withTol(10).drive(1000);
          intake.justOneBall(1).goalSort(alliance, 70, HOLDBALL);
          // intake.middleSpinVelocity(600);
          // intake.indexerSpinVelocity(200);
          // pros::delay(400);
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
        case 6: {
          chassis.withPD(0.6,0.001).withSlew(2).withHeading(0,1).withTol(10).drive(-450);
          chassis.withTurnPD(1,1).withTurnSlew(1).withTurnDirection(LEFT).withTol(1).turn(15).waitUntilSettled();
          currentPos = 6;}//robot's mvmt from 3 to 6
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
        case 3: {
          chassis.withPD(0.2,0.001).withSlew(75).withHeading(0).withTol(10).drive(-725);
          chassis.withTurnPD(1.1,1).justPD(1).withTurnDirection(RIGHT).withTol(1).turn(90).waitUntilSettled();
          chassis.withPD(0.2,0.001).withSlew(120).withHeading(0).autoSort(1).withTol(10).withDist(40).drive(1200);
          intake.justOneBall(1).goalSort(alliance, 100, HOLDBALL);
          chassis.withPD(0.2,0.001).withSlew(75).withHeading(0).withTol(10).drive(-300);
          currentPos = 3;break;}//robot's mvmt from 6 to 3
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
          chassis.withPD(.3,0.001).withSlew(100).withHeading(283,1).withTol(10).drive(-600);
          pros::delay(200);
          chassis.withTurnPD(1.125,.1).justPD(1).withTurnDirection(LEFT).withTol(1).turn(143).waitUntilSettled();
          intake.dropBall();
          chassis.withPD(0.25,0.001).withSlew(200).withHeading(143,1).autoSort(1).withTol(10).drive(2550);
          chassis.withTurnPD(1.25,.1).withTurnDirection(RIGHT).justPD(1).withTol(1).turn(190).waitUntilSettled();
          // pros::delay(200);
          chassis.withPD(1,0.001).withSlew(115).withHeading(185,1).autoSort(1).withDist(50).withTol(50).drive(1000);
          intake.justOneBall(1).goalSort(alliance, 70, HOLDBALL);
          chassis.withPD(1,0.001).withSlew(100).withHeading(185,1).withTol(10).drive(-500);
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
  chassis.setState(HOLD);
  intake.iiInit();
  intake.indexerSpinVelocity(200);
  //Goal 1 (G)

  pros::delay(100);
  intake.indexerStop();
  chassis.withPD(0.4,0.01).withSlew(150).withHeading(10,3).autoSort(1).withTol(10).drive(1950);
  chassis.withTurnPD(1.25,1).withTurnSlew(1).withTurnDirection(LEFT).withTol(1).turn(240).waitUntilSettled();
  chassis.withPD(0.35,0.001).withSlew(150).withHeading(240).autoSort(0).withDist(40).withTol(50).drive(1200);
  intake.middleSpinVelocity(-600);
  pros::delay(100);
  intake.justOneBall(1).goalSort(REDBALL, 60, HOLDBALL);
  //Goal 2 (D)

  chassis.withPD(0.2,0.001).withSlew(50).withHeading(240).withTol(10).drive(-200);
  chassis.withTurnPD(1.119,1).withTurnDirection(RIGHT).justPD(1).withTol(1).turn(330).waitUntilSettled();
  intake.dropBall();
  chassis.withPD(0.3,1).withSlew(150).withHeading(330,1).autoSort(1).withTol(10).drive(1400);
  chassis.withTurnPD(1.32,1).withTurnSlew(1).withTurnDirection(LEFT).withTol(1).turn(290).waitUntilSettled();
  chassis.withPD(0.2,1).withSlew(100).withHeading(290).autoSort(0).withDist(45).withTol(10).drive(1000);
  intake.goalSort(REDBALL, 50, HOLDBALL);
  // intake.indexerSpinVelocity(-200);
  //Goal 3 (A)

  intake.dropBall(REVERSE);
  chassis.withPD(0.2,0.001).withSlew(50).withHeading(270).withTol(10).drive(-1300);
  chassis.withTurnPD(.45,0.1).withTurnDirection(RIGHT).justPD(1).withTol(1).turn(60).waitUntilSettled();
  chassis.withPD(0.25,0.001).withSlew(100).withHeading(60).autoSort(1).withTol(10).drive(800);
  chassis.withTurnPD(.24,1).withTurnDirection(LEFT).justPD(1).withTol(1).turn(328).waitUntilSettled();
  chassis.withPD(0.2,0.001).withSlew(100).withHeading(327).autoSort(1).withDist(45).withTol(10).drive(1600);
  intake.middleSpinVelocity(-600);
  pros::delay(100);
  intake.justOneBall(1).goalSort(REDBALL, 90, HOLDBALL);
  // intake.indexerSpinVelocity(-200);
  // Goal 4 (B)

  chassis.withPD(0.2,0.001).withSlew(50).withHeading(300).withTol(10).drive(-100);
  chassis.withTurnPD(.925,1).withTurnDirection(RIGHT).justPD(1).withTol(1).turn(81).waitUntilSettled();
  intake.dropBall();
  chassis.withPD(0.3,0.001).withSlew(150).withHeading(81).autoSort(1).withTol(10).drive(1050);
  chassis.withTurnPD(.4,.1).withTurnSlew(1).withTurnDirection(LEFT).justPD(1).withTol(1).turn(310).waitUntilSettled();
  chassis.withPD(1,0.001).withSlew(150).withHeading(310).autoSort(1).withTol(50).drive(650);
  chassis.withTurnPD(.4,.1).withTurnSlew(1).withTurnDirection(RIGHT).justPD(1).withTol(1).turn(0).waitUntilSettled();
  chassis.withPD(0.2,0.001).withSlew(75).withHeading(0,2).withDist(50).withTol(10).drive(1000);
  intake.goalSort(REDBALL, 50, HOLDBALL);
  // Goal 5 (C)

  chassis.withPD(0.25,0.001).withSlew(50).withHeading(0).withTol(10).drive(-715);
  chassis.withTurnPD(1.2,.1).withTurnSlew(1).withTurnDirection(RIGHT).justPD(1).withTol(1).turn(150).waitUntilSettled();
  intake.dropBall();
  chassis.withPD(0.4,0.001).withSlew(200).withHeading(150,1).autoSort(1).withTol(10).drive(1100);
  chassis.withTurnPD(1,.1).withTurnDirection(LEFT).justPD(1).withTol(1).turn(55).waitUntilSettled();
  chassis.withPD(0.4,0.001).withSlew(100).withHeading(55).withDist(50).withTol(10).drive(1200);
  intake.justOneBall(1).goalSort(REDBALL, 50, HOLDBALL);
  //Goal 6 (F)

  chassis.withPD(0.2,0.001).withSlew(50).withHeading(55).withTol(10).drive(-100);
  chassis.withTurnPD(1,1).withTurnSlew(1).withTurnDirection(RIGHT).justPD(1).withTol(1).turn(150).waitUntilSettled();
  intake.dropBall();
  chassis.withPD(0.4,0.001).withSlew(150).withHeading(150,1).autoSort(1).withTol(10).drive(1000);
  chassis.withTurnPD(1.2,.1).withTurnSlew(1).withTurnDirection(LEFT).justPD(1).withTol(2).turn(95).waitUntilSettled();
  chassis.withPD(0.2,0.001).withSlew(100).withHeading(90).withDist(50).withTol(1).drive(1200);
  intake.goalSort(REDBALL, 55, HOLDBALL);
  //Goal 7 (I)

  chassis.withPD(0.2,0.001).withSlew(50).withHeading(95).withTol(10).drive(-325);
  chassis.withTurnPD(1.2,0.1).withTurnDirection(RIGHT).justPD(1).withTol(1).turn(267).waitUntilSettled();
  intake.dropBall();
  chassis.withPD(0.3,0.001).withSlew(150).withHeading(267,1).autoSort(1).withTol(10).drive(1050);
  chassis.withTurnPD(1.1,1).withTurnDirection(LEFT).justPD(1).withTol(1).turn(148).waitUntilSettled();
  chassis.withPD(0.2,0.001).withSlew(120).withHeading(148).autoSort(1).withDist(45).withTol(10).drive(1600);
  intake.middleSpinVelocity(-600);
  pros::delay(100);
  intake.justOneBall(1).goalSort(REDBALL, 90, HOLDBALL);
  chassis.withPD(0.2,0.001).withSlew(50).withHeading(95).withTol(10).drive(-325);

  //Goal 8 (H)
  /*
  chassis.withPD(0.4,0.001).withSlew(1).withHeading(135).drive(-1000);
  chassis.withTurnPD(1,1).withTurnSlew(1).withTurnDirection(LEFT).justPD(1).turn(315).waitUntilSettled();
  chassis.withPD(0.4,0.001).withSlew(1).withHeading(315).autoSort(1).drive(2000);
  intake.indexerSpinVelocity(200);
  //Goal 9 (E)
*/

  return *this;
}
