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
          chassis.setState(HOLD);
          // intake.iinit();
          intake.deploy();
          // intake.indexerSpinVelocity(200);
          // pros::delay(200);
          // intake.indexerStop();
          currentPos = 3; break; }//robot's mvmt from 1 to 3
        case 4: {currentPos = 4; }//robot's mvmt from 1 to 4
        case 5: {currentPos = 5; }//robot's mvmt from 1 to 5
        case 6: {
          chassis.setState(HOLD);
          chassis.withPD(.3,0.001).withSlew(200).withHeading(1,1).autoSort(1).withTol(10).withDist(45).drive(3000);
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
          intake.deploy();
          // intake.indexerSpinVelocity(200);
          // pros::delay(200);
          // intake.indexerStop();
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
          chassis.withPD(0.225,0.001).withSlew(150).withHeading(0,1).withTol(10).drive(1400);
          pros::delay(200);
          chassis.withTurnPD(1.56,1).withTurnSlew(1).withTurnDirection(LEFT).withTol(1).turn(280).waitUntilSettled();
          // chassis.withPD(0.22,0.001).withSlew(1).withHeading(270).drive(900);
          chassis.withPD(.5,0.001).withSlew(125).withHeading(280,1).autoSort(1).withDist(45).withTol(10).drive(1000);
          intake.justOneBall(1).goalSort(alliance, 70, HOLDBALL);
          chassis.withPD(.3,0.001).withSlew(75).withHeading(283,1).withTol(10).drive(-850);
          // intake.middleSpinVelocity(600);
          // intake.indexerSpinVelocity(200);
          // pros::delay(400);
          currentPos = 1; break;
        }//robot's mvmt from 2 to 1
        case 3: {//robot's mvmt from 2 to 3
        chassis.withPD(0.3,0.001).withSlew(150).withHeading(0,1).withTol(10).drive(1450);
        pros::delay(200);
        chassis.withTurnPD(1.56,1).withTurnSlew(1).withTurnDirection(RIGHT).withTol(1).turn(80).waitUntilSettled();
        chassis.withPD(.5,0.001).withSlew(125).withHeading(80,1).autoSort(1).withDist(40).withTol(10).drive(1200);
        intake.justOneBall(1).goalSort(alliance, 70, HOLDBALL);
        intake.indexerStop();
        intake.middleStop();
        chassis.driveDistAway(500);
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
          chassis.withPD(0.2,0.001).withSlew(75).withHeading(0).withTol(10).drive(-1000);
          chassis.withTurnPD(1.1,1).justPD(1).withTurnDirection(RIGHT).withTol(1).turn(90).waitUntilSettled();
          chassis.withPD(0.2,0.001).withSlew(100).withHeading(0).autoSort(1).withTol(10).withDist(45).drive(1200);
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
          // chassis.withPD(.3,0.001).withSlew(75).withHeading(283,1).withTol(10).drive(-850);
          pros::delay(200);
          chassis.withTurnPD(1.13,.1).justPD(1).withTurnDirection(LEFT).withTol(1).turn(143).waitUntilSettled();
          intake.dropBall();
          chassis.withPD(0.15,0.001).withSlew(200).withHeading(143,2).autoSort(1).withTol(10).drive(3250);
          chassis.withTurnPD(1.25,.1).withTurnDirection(RIGHT).justPD(1).withTol(1).turn(187).waitUntilSettled();
          // pros::delay(200);
          chassis.withPD(.2,0.001).withSlew(125).withHeading(187,1).autoSort(1).withDist(45).withTol(10).drive(1200);
          intake.justOneBall(1).goalSort(alliance, 70, HOLDBALL);
          // chassis.withPD(.3,0.001).withSlew(150).withHeading(185,1).withTol(10).drive(-);
          chassis.driveDistAway(200);
          intake.dropBall(REVERSE);
          // chassis.withTurnPD(1,.1).justPD(1).withTurnDirection(LEFT).withTol(1).turn(135).waitUntilSettled();
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
          // chassis.withPD(.3,0.001).withSlew(75).withHeading(283,1).withTol(10).drive(-475);
          pros::delay(200);
          chassis.withTurnPD(1.13,.1).justPD(1).withTurnDirection(RIGHT).withTol(1).turn(217).waitUntilSettled();
          intake.dropBall();
          chassis.withPD(0.15,0.0001).withSlew(200).withHeading(143,2).autoSort(1).withTol(10).drive(3700);
          chassis.withTurnPD(1.25,.1).withTurnDirection(LEFT).justPD(1).withTol(1).turn(170).waitUntilSettled();
          // pros::delay(200);
          chassis.withPD(.2,0.001).withSlew(125).withHeading(280,1).autoSort(1).withDist(45).withTol(10).drive(1200);
          intake.justOneBall(1).goalSort(alliance, 70, HOLDBALL);
          chassis.withPD(.3,0.001).withSlew(150).withHeading(185,1).withTol(10).drive(-300);
          intake.dropBall(REVERSE);
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
  intake.deploy();
  // intake.iiInit();
  // intake.intakeSpin(600);
  // intake.indexerSpinVelocity(200);
  //Goal 1 (G)

  pros::delay(100);
  intake.indexerStop();
  chassis.withPD(0.3,0.0001).withSlew(140).withHeading(10,3).autoSort(1).withTol(10).drive(2400);
  chassis.withTurnPD(1.3,1).withTurnSlew(1).withTurnDirection(LEFT).withTol(1).turn(245).waitUntilSettled();
  chassis.withPD(0.35,0.001).withSlew(150).withHeading(245).autoSort(0).withDist(35).withTol(50).drive(1200);
  intake.middleSpinVelocity(-600);
  pros::delay(100);
  intake.justOneBall(1).goalSort(REDBALL, 60, HOLDBALL);
  //Goal 2 (D)

  // chassis.withPD(0.2,0.001).withSlew(50).withHeading(245).withTol(10).drive(-150);
  chassis.driveDistAway(100);
  chassis.withTurnPD(1.1125,1).withTurnDirection(RIGHT).justPD(1).withTol(1).turn(330).waitUntilSettled();
  intake.dropBall();
  chassis.withPD(0.3,1).withSlew(150).withHeading(330,1).autoSort(1).withTol(10).drive(1850);
  chassis.withTurnPD(1.32,1).withTurnSlew(1).withTurnDirection(LEFT).withTol(1).turn(290).waitUntilSettled();
  chassis.withPD(0.2,1).withSlew(100).withHeading(290).autoSort(0).withDist(45).withTol(10).drive(1000);
  intake.goalSort(REDBALL, 50, HOLDBALL);
  // intake.indexerSpinVelocity(-200);
  //Goal 3 (A)

  chassis.withPD(0.2,0.001).withSlew(50).withHeading(270).withTol(10).drive(-100);
  chassis.withTurnPD(.96,0.1).withTurnDirection(RIGHT).justPD(1).withTol(1).turn(90).waitUntilSettled();
  intake.dropBall(EJECT);
  chassis.withPD(0.3,0.001).withSlew(150).withHeading(90).autoSort(1).withTol(10).drive(2550);
  chassis.withTurnPD(.23,1).withTurnDirection(LEFT).justPD(1).withTol(1).turn(328).waitUntilSettled();
  chassis.withPD(0.2,0.001).withSlew(100).withHeading(327).autoSort(1).withDist(45).withTol(10).drive(1600);
  intake.middleSpinVelocity(-600);
  pros::delay(100);
  // intake.justOneBall(1).goalSort(REDBALL, 90, HOLDBALL);
  intake.middleSpinVelocity(600);
  intake.indexerSpinVelocity(200);
  pros::delay(500);
  // Goal 4 (B)

  chassis.withPD(0.2,0.001).withSlew(50).withHeading(300).withTol(10).drive(-140);
  chassis.withTurnPD(.93,1).withTurnDirection(RIGHT).justPD(1).withTol(1).turn(76).waitUntilSettled();
  intake.dropBall();
  chassis.withPD(0.3,0.001).withSlew(150).withHeading(76).autoSort(1).withTol(10).drive(2000);
  chassis.withTurnPD(.395,.1).withTurnSlew(1).withTurnDirection(LEFT).justPD(1).withTol(1).turn(305).waitUntilSettled();
  chassis.withPD(.2,0.001).withSlew(130).withHeading(305).autoSort(1).withTol(50).drive(880);
  chassis.withPD(.2,0.001).withSlew(50).withHeading(305).autoSort(1).withTol(50).drive(-285);
  chassis.withTurnPD(.25,.1).withTurnSlew(1).withTurnDirection(RIGHT).justPD(1).withTol(10).turn(5).waitUntilSettled();
  chassis.withPD(0.2,0.001).withSlew(75).withHeading(0,2).withDist(50).withTol(10).drive(1000);
  intake.goalSort(REDBALL, 50, HOLDBALL);
  // Goal 5 (C)

  chassis.withPD(0.25,0.001).withSlew(50).withHeading(147).withTol(10).drive(-1150);
  chassis.withTurnPD(1.15,.1).withTurnSlew(1).withTurnDirection(RIGHT).justPD(1).withTol(1).turn(150).waitUntilSettled();
  intake.dropBall();
  chassis.withPD(0.35,0.001).withSlew(150).withHeading(150,1).autoSort(1).withTol(10).drive(1750);
  chassis.withTurnPD(1.1,.1).withTurnDirection(LEFT).justPD(1).withTol(1).turn(65).waitUntilSettled();
  chassis.withPD(0.5,0.001).withSlew(100).withHeading(65).withDist(50).withTol(10).drive(1500);
  intake.justOneBall(1).goalSort(REDBALL, 50, HOLDBALL);
  //Goal 6 (F)

  chassis.withPD(0.2,0.001).withSlew(50).withHeading(67).withTol(10).drive(-100);
  chassis.withTurnPD(1.01,1).withTurnSlew(1).withTurnDirection(RIGHT).justPD(1).withTol(1).turn(155).waitUntilSettled();
  intake.dropBall();
  chassis.withPD(0.3,0.001).withSlew(150).withHeading(150,1).autoSort(1).withTol(10).drive(2100);
  chassis.withTurnPD(1.2,.1).withTurnSlew(1).withTurnDirection(LEFT).justPD(1).withTol(2).turn(100).waitUntilSettled();
  chassis.withPD(0.2,0.001).withSlew(100).withHeading(90).withDist(50).withTol(1).drive(1200);
  intake.goalSort(REDBALL, 55, HOLDBALL);
  //Goal 7 (I)

  chassis.withPD(0.2,0.001).withSlew(50).withHeading(95).withTol(10).drive(-325);
  chassis.withTurnPD(1.2,0.1).withTurnDirection(RIGHT).justPD(1).withTol(1).turn(267).waitUntilSettled();
  intake.dropBall();
  chassis.withPD(0.3,0.001).withSlew(150).withHeading(267,1).autoSort(1).withTol(10).drive(2250);
  // chassis.withPD(0.3,0.001).withSlew(150).withHeading(267,1).autoSort(1).withTol(10).drive(-100);
  // chassis.withTurnPD(1,1).withTurnDirection(RIGHT).justPD(1).withTol(1).turn(330).waitUntilSettled();
  // chassis.withPD(0.3,0.001).withSlew(150).withHeading(267,1).autoSort(1).withTol(10).drive(500);
  // chassis.withPD(0.3,0.001).withSlew(150).withHeading(267,1).autoSort(1).withTol(10).drive(-100);
  // chassis.withPD(0.3,0.001).withSlew(150).withHeading(267,1).autoSort(1).withTol(10).drive(250);
  // chassis.withTurnPD(2,1).withTurnDirection(LEFT).justPD(1).withTol(20).turn(300).waitUntilSettled();
  // chassis.withPD(0.3,0.001).withSlew(150).withHeading(267,1).autoSort(1).withDist(45).withTol(10).drive(500);
  // intake.indexerSpinVelocity(200);
  // chassis.driveDistAway(550);
  // chassis.withTurnPD(2,1).withTurnDirection(LEFT).justPD(1).withTol(20).turn(180).waitUntilSettled();
  // chassis.withPD(0.2,0.001).withSlew(150).withHeading(148).autoSort(1).withTol(10).drive(1500);
  // Goal 8 Middle

  chassis.withTurnPD(1.1,1).withTurnDirection(LEFT).justPD(1).withTol(1).turn(148).waitUntilSettled();
  chassis.withPD(0.2,0.001).withSlew(120).withHeading(148).autoSort(1).withDist(45).withTol(10).drive(1600);
  intake.middleSpinVelocity(-600);
  pros::delay(100);
  intake.justOneBall(1).goalSort(REDBALL, 90, HOLDBALL);
  chassis.withPD(0.2,0.001).withSlew(50).withHeading(95).withTol(10).drive(-325);
  //Goal 9
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
