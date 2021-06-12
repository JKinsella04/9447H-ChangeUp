#include "main.h"
#include "class/control/auton.hpp"
#include "class/control/chassis.hpp"
#include "class/control/intakes.hpp"
// #include "class/control/misc.hpp"

static Chassis chassis;
static Intake intake;
// static motionProfile motionProfile;

/*
for starting kP, kI, kD values
big distance
kP - .1
kI - 0.001
kD - 0.03

short distance
kP - .3
kI - 0.01
kD - 0.15

for starting turn kP, kI, kD values
kP - 66, 133, 266
kI - 0.001
kD - 33, 66, 133
*/
Auton& Auton::run(){
 while(true){
 // blueAutoSortTask.suspend();
 // redAutoSortTask.suspend();
  switch (startPos) { //Where am I? Starting Position
    case 1: {
      switch (firstPos) {
        case 1: { //robot's mvmt from 1 to 1 //
          intake.deploy();
          chassis.setState(COAST);
            // chassis.withPD(0.6,1.175).withSlew(450).withHeading(350,1).autoSort(1).withTol(25).drive(1000).waitUntilSettled(0);
          // chassis.withPD(1.75,1).withSlew(350).withHeading(350,.1).withTol(10).withDist(80).driveCurve(1000,1,.075);
          // chassis.autoSort(1).withSlop(1000, 3).withTurn(345, 133, 0.018 ,66).move(20, 0.3, 0.01, 0.15);
          // chassis.withTurnPD(200000000,.1).withTurnSlew(2).turn(90).waitUntilSettled();
          currentPos = 1; break;}
        case 2: { //robot's mvmt from 1 to 2
          chassis.setState(HOLD);
          // intake.iinit();
          intake.deploy();
          currentPos = 2; break;}
        case 3: {
          chassis.setState(HOLD);
          // intake.iinit();
          intake.deploy();
          // intake..intakeSpinVelocity(600).indexerSpinVelocity(200);
          // pros::delay(200);
          intake.indexerStop();
          currentPos = 3; break; }//robot's mvmt from 1 to 3
        case 4: {currentPos = 4; }//robot's mvmt from 1 to 4
        case 5: {currentPos = 5; }//robot's mvmt from 1 to 5
        case 6: {
          chassis.setState(HOLD);
          chassis.withPD(.3,0.001).withSlew(600).withHeading(1,1).autoSort(1).withTol(10).withDist(45).drive(3000);
          // intake.goalSort(alliance, 100, SHOOTBALL);
          currentPos = 6; }//robot's mvmt from 1 to 6
        default: { startPos=0;break;}
      } }
    case 2: {
      switch (firstPos) {
        case 1: { //////////////////////////////////////////////////////////
          intake.deploy();
          chassis.setState(HOLD);
          chassis.withPD(1.75,1).withSlew(350).withHeading(345,.1).withDist(80).withTol(10).driveCurve(1000,.25,.075);
          pros::delay(200);
          intake.twoBall(0).goalSort(alliance, 120);
          // 2011 Home Row auton HERE
          // chassis.withSlop(10000, 5).withTurn(0, 50, 0, 0).move(-50, 0.1, 0.01, 0.05);

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
        case 2: { //////////////////////////////////////////////////////////
          intake.dropBall();
          chassis.withPD(.65,.325).withSlew(350).withHeading(0,.1).withTol(50).driveCurve(-1900,.2,.075);
          chassis.withTurnPD(4,2).justPD(1).withTol(3).turn(270).waitUntilSettled();
          chassis.withPD(1.75,1).withSlew(350).withHeading(270,.1).withDist(100).withTol(10).driveCurve(1000, .25, .075);
          intake.twoBall(0).goalSort(alliance, 90);
          chassis.withPD(.7,.375).justPD(1).withHeading(270,.1).withTol(10).driveCurve(-200, .25, .075);
          currentPos = 2; break;}//robot's mvmt from 1 to 2
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
          chassis.withPD(.6,0.9).withSlew(500).withHeading(0,.1).withTol(10).drive(1500);
          pros::delay(200);
          chassis.withTurnPD(4,2).justPD(1).withTol(1).turn(280).waitUntilSettled();
          chassis.withPD(1,1).withSlew(425).withHeading(280,.25).autoSort(1).withDist(60).withTol(10).drive(1100);
          // intake.intakeStop();
          intake.intakeSpin(-12000);
          intake.rollerSpin(12000);
          // intake.middleSpinVelocity(12000);
          // intake.indexerSpin(12000);
          pros::delay(600);
          // chassis.withPD(.3,1).withSlew(175).withHeading(285,.25).withTol(10).drive(-850);
          // intake.middleSpinVelocity(600);
          // intake.indexerSpinVelocity(200);
          // pros::delay(400);
          currentPos = 1; break;
        }//robot's mvmt from 2 to 1
        case 3: {//robot's mvmt from 2 to 3
        chassis.withPD(.6,0.8).withSlew(500).withHeading(0,.1).withTol(10).drive(1500);
        // chassis.withPD(.6,1.175).withSlew(500).withHeading(0,.25).withTol(10).drive(1500);
        pros::delay(200);
        chassis.withTurnPD(4,2).justPD(1).withTol(1).turn(85).waitUntilSettled();
        chassis.withPD(1,1).withSlew(425).withHeading(85,.25).autoSort(1).withDist(60).withTol(10).drive(1100);
        intake.intakeSpin(-12000);
        intake.rollerSpin(12000);
        pros::delay(600);
        // intake.middleSpinVelocity(12000);
        // intake.indexerSpin(12000);
        // chassis.withPD(.3,1).withSlew(175).withHeading(215,.25).withTol(10).drive(-850);
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
          // intake.justOneBall(1).goalSort(alliance, 100, HOLDBALL);
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
          // chassis.withTurnPD(4,2).justPD(1).withTurnDirection(RIGHT).withTol(1).turn(215).waitUntilSettled();
          intake.dropBall();
          intake.intakeSpin(-12000);
          pros::delay(200);
          chassis.withPD(1.75,1).withSlew(350).withHeading(325,.1).withTol(100).driveCurve(-3900,.175,.075);
          chassis.withTurnPD(4,2).justPD(1).withTol(1).turn(190).waitUntilSettled();
          // pros::delay(200);
          chassis.withPD(1,1).withSlew(600).withHeading(190,.1).autoSort(1).withDist(60).withTol(10).drive(1800);
          intake.intakeSpin(-12000);
          intake.rollerSpin(12000);
          // intake.middleSpin(12000);
          // intake.indexerSpin(12000);
          // intake.justOneBall(1).goalSort(alliance, 70, HOLDBALL);
          // chassis.withPD(.3,0.001).withSlew(150).withHeading(185,1).withTol(10).drive(-);
          // chassis.driveDistAway(200);
          // intake.dropBall();
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
        case 3: { //////////////////////////////////////////////////////////
          intake.dropBall();
          chassis.withTurnPD(4,2).justPD(1).withTol(3).turn(345).waitUntilSettled();
          // chassis.withPD(.65,.1).withSlew(350).withHeading(0,.1).withTol(50).driveCurve(-1900,.2,.075);
          chassis.withPD(.75,.375).withSlew(350).withHeading(0,.1).withTol(50).driveCurve(-1400,.2,.075);
          // chassis.withPD(.75,.25).justPD(1).withHeading(0,.1).withTol(10).driveCurve(-1500,.3,.075);
          chassis.withTurnPD(4,2).justPD(1).withTol(3).turn(225).waitUntilSettled();
          chassis.setState(COAST);
          // chassis.autoSort(1).withPD(1.75,1).withSlew(600).withHeading(225,.1).withDist(100).withTol(10).driveCurve(1200, .25, .075);
          // intake.twoBall(0).goalSort(alliance, 90);
          // chassis.withPD(.7,.5).justPD(1).withHeading(225,.1).withTol(10).driveCurve(-250, .25, .075);
          currentPos = 3; break;}//robot's mvmt from 2 to 3
        case 4: {currentPos = 4;}//robot's mvmt from 2 to 4
        case 5: {currentPos = 5;}//robot's mvmt from 2 to 5
        case 6: {currentPos = 6;}//robot's mvmt from 2 to 6
      }}
    case 3: {
      switch (thirdPos) {
        case 1: {
          // chassis.withPD(.3,0.001).withSlew(75).witHeading(283,1).withTol(10).drive(-475);
          pros::delay(200);
          // chassis.withTurnPD(4,2).justPD(1).withTurnDirection(RIGHT).withTol(1).turn(215).waitUntilSettled();
          intake.dropBall();
          intake.intakeSpin(-12000);
          pros::delay(200);
          chassis.withPD(1.75,1).withSlew(350).withHeading(35,.1).withTol(75).driveCurve(-3800,.175,.075);
          chassis.withTurnPD(4,2).justPD(1).withTol(1).turn(175).waitUntilSettled();
          // pros::delay(200);
          chassis.withPD(1,1).withSlew(600).withHeading(180,.1).autoSort(1).withDist(60).withTol(10).drive(1800);
          intake.intakeSpin(-12000);
          intake.rollerSpin(12000);
          // intake.middleSpin(12000);
          // intake.indexerSpin(12000);
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
  // chassis.withTurn(0, .1, .1,.1).move(1500, .3,.1,.1).waitUntilSettled();

  chassis.setState(HOLD);
  intake.deploy();
  intake.iiInit();
  // intake.intakeSpin(600);
  // intake.indexerSpinVelocity(200);
  //Goal 1 (G)

  // pros::delay(100);
  // intake.indexerStop();
  // chassis.withPD(.6,1.175).withSlew(550).withHeading(0,.25).withTol(10).drive(1500);
  intake.intakeSpin(12000);
  // chassis.autoSort(1).withSlop(1000, 3).withTurn(10, 540, 0.01, 133).move(63, .3, 0.015 ,0.15).waitUntilSettled();
  chassis.withPD(0.6,1.175).withSlew(450).withHeading(5,.1).autoSort(1).withTol(25).drive(2500).waitUntilSettled(0);
  chassis.withTurnPD(4,2).justPD(1).withTol(1).turn(240).waitUntilSettled();
  chassis.withPD(0.6,1.175).withSlew(500).withHeading(240,.1).autoSort(1).withDist(60).withTol(10).drive(2500);
  intake.middleSpinVelocity(-600);
  pros::delay(100);
  intake.twoBall(0).goalSort(REDBALL, 90);
  // chassis.driveDistAway(250);
  chassis.withPD(0.8,1.175).withSlew(200).justPD(1).withHeading(355,.1).autoSort(1).withTol(10).drive(-350);
  chassis.withTurnPD(4,2).justPD(1).withTol(1).turn(200).waitUntilSettled();
  intake.intakeSpin(-12000);
  intake.rollerSpin(-12000);
  pros::delay(250);
  // chassis.withTurnPD(4,2).justPD(1).withTol(1).turn(245).waitUntilSettled();

  // intake.justOneBall(1).goalSort(REDBALL, 60, HOLDBALL);
  //Goal 2 (D)
  // chassis.withPD(0.2,0.001).withSlew(50).withHeading(245).withTol(10).drive(-150);
  // chassis.driveDistAway(100);
  chassis.withTurnPD(4,2).justPD(1).withTol(1).turn(330).waitUntilSettled();
  // chassis.withTurnPD(1.1125,1).withTurnDirection(RIGHT).justPD(1).withTol(1).turn(330).waitUntilSettled();
  // intake.dropBall();
  chassis.withPD(0.6,1.175).withSlew(500).justPD(1).withHeading(330,.1).autoSort(1).withTol(10).drive(1850).waitUntilSettled(0);
  chassis.withTurnPD(3,2).justPD(1).withTol(3).turn(355).waitUntilSettled();
  chassis.withPD(0.6,1.175).withSlew(500).withHeading(355,.1).autoSort(1).withTol(10).drive(600);
  chassis.withPD(1,1.175).withSlew(200).justPD(1).withHeading(355,.1).autoSort(1).withTol(10).drive(-300);
  chassis.withTurnPD(4,2).justPD(1).withTol(1).turn(290).waitUntilSettled();
  // chassis.withTurnPD(1.32,1).withTurnSlew(1).withTurnDirection(LEFT).withTol(1).turn(290).waitUntilSettled();
  chassis.withPD(0.6,1.175).withSlew(500).withHeading(290,.1).withDist(80).withTol(10).drive(1200);
  // chassis.withPD(0.2,1).withSlew(100).withHeading(290).autoSort(0).withDist(45).withTol(10).drive(1000);
  intake.indexerSpin(200);
  pros::delay(200);
  intake.twoBall(1).goalSort(REDBALL, 90);
  // intake.justOneBall(0).goalSort(REDBALL, 60, HOLDBALL);
  // intake.indexerSpinVelocity(-200);
  //Goal 3 (A)

  // chassis.withPD(0.2,0.001).withSlew(50).withHeading(270).withTol(10).drive(-100);
  // chassis.driveDistAway(250);
  // chassis.withTurnPD(.96,0.1).withTurnDirection(RIGHT).justPD(1).withTol(1).turn(90).waitUntilSettled();
  // intake.dropBall();
  // chassis.withPD(0.3,2.2).withSlew(150).withHeading(90).autoSort(1).withTol(10).drive(2200);
  intake.rollerSpin(-12000);
  intake.intakeSpin(-12000);
  chassis.withPD(.8,1.175).withSlew(200).justPD(1).withHeading(290,.1).withTol(10).drive(-400);
  chassis.withTurnPD(3,2).justPD(1).withTol(1).turn(89).waitUntilSettled();
  chassis.withPD(0.5,1.175).withSlew(400).justPD(1).withHeading(89,.1).autoSort(1).withTol(10).drive(2300);
  chassis.withTurnPD(2,.5).justPD(1).withTol(1).turn(327).waitUntilSettled();
  chassis.withPD(0.6,1.175).withSlew(500).justPD(0).withHeading(327,.1).autoSort(1).withDist(80).withTol(10).drive(1200);
  intake.indexerSpin(200);
  pros::delay(200);
  intake.twoBall(0).goalSort(REDBALL, 90);

  // chassis.withPD(0.6,1.175).withSlew(200).justPD(1).withHeading(290,.1).withTol(10).drive(250);

  // chassis.withTurnPD(.235,1).withTurnDirection(LEFT).justPD(1).withTol(1).turn(328).waitUntilSettled();
  // chassis.withPD(0.2,1).withSlew(100).withHeading(328).autoSort(1).withDist(45).withTol(10).drive(1600);
  // intake.middleSpinVelocity(-600);
  // pros::delay(100);
  // intake.justOneBall(1).goalSort(REDBALL, 90, HOLDBALL);
  // intake.middleSpinVelocity(600);
  // intake.indexerSpinVelocity(200);
  // pros::delay(500);
  // Goal 4 (B)
  chassis.withPD(.8,1.175).withSlew(200).justPD(1).withHeading(290,.1).withTol(10).drive(-400);
  chassis.withTurnPD(4,2).justPD(1).withTol(1).turn(310).waitUntilSettled();
  intake.intakeSpin(-12000);
  intake.rollerSpin(-12000);
  pros::delay(250);
  chassis.withTurnPD(1,.5).justPD(1).withTol(1).turn(70).waitUntilSettled();
  chassis.withPD(0.5,1.175).withSlew(400).justPD(1).withHeading(70,.1).autoSort(1).withTol(10).drive(2000);

  /*
  chassis.withPD(0.2,1).withSlew(50).withHeading(300).withTol(10).drive(-140);
  chassis.withTurnPD(.93,1).withTurnDirection(RIGHT).justPD(1).withTol(1).turn(76).waitUntilSettled();
  intake.dropBall();
  chassis.withPD(0.3,1.5).withSlew(150).withHeading(76).autoSort(1).withTol(10).drive(2000);
  chassis.withTurnPD(.385,.1).withTurnSlew(1).withTurnDirection(LEFT).justPD(1).withTol(1).turn(305).waitUntilSettled();
  chassis.withPD(.2,1).withSlew(130).withHeading(305).autoSort(1).withTol(50).drive(950);
  chassis.withPD(.2,1).withSlew(50).withHeading(305).autoSort(1).withTol(50).drive(-350);
  chassis.withTurnPD(.25,.1).withTurnSlew(1).withTurnDirection(RIGHT).justPD(1).withTol(10).turn(5).waitUntilSettled();
  chassis.withPD(0.2,1).withSlew(75).withHeading(0,2).withDist(50).withTol(10).drive(1200);
  intake.indexerSpin(200);
  pros::delay(200);
  // intake.justOneBall(0).goalSort(REDBALL, 50, HOLDBALL);
  // Goal 5 (C)

  chassis.withPD(0.25,1).withSlew(50).withHeading(147).withTol(10).drive(-1400);
  chassis.withTurnPD(1,.1).withTurnSlew(1).withTurnDirection(RIGHT).justPD(1).withTol(1).turn(147).waitUntilSettled();
  intake.dropBall();
  chassis.withPD(0.35,1.75).withSlew(150).withHeading(147,1).autoSort(1).withTol(10).drive(1550);
  chassis.withTurnPD(1,.1).withTurnDirection(LEFT).justPD(1).withTol(1).turn(65).waitUntilSettled();
  chassis.withPD(0.5,1).withSlew(100).withHeading(65).withDist(50).withTol(10).drive(1500);
  // intake.justOneBall(1).goalSort(REDBALL, 50, HOLDBALL);
  //Goal 6 (F)

  chassis.driveDistAway(100);
  chassis.withTurnPD(1.01,1).withTurnSlew(1).withTurnDirection(RIGHT).justPD(1).withTol(1).turn(155).waitUntilSettled();
  intake.dropBall();
  chassis.withPD(0.3,1).withSlew(150).withHeading(150,1).autoSort(1).withTol(10).drive(2100);
  chassis.withTurnPD(1.2,.1).withTurnSlew(1).withTurnDirection(LEFT).justPD(1).withTol(2).turn(100).waitUntilSettled();
  chassis.withPD(0.2,1).withSlew(100).withHeading(90).withDist(50).withTol(1).drive(1200);
  intake.indexerSpin(200);
  pros::delay(200);
  // intake.justOneBall(0).goalSort(REDBALL, 55, HOLDBALL);
  //Goal 7 (I)

  chassis.withPD(0.2,1).withSlew(50).withHeading(95).withTol(10).drive(-325);
  chassis.withTurnPD(1,0.1).withTurnDirection(RIGHT).justPD(1).withTol(1).turn(270).waitUntilSettled();
  intake.dropBall();
  chassis.withPD(0.3,1).withSlew(150).withHeading(270,1).autoSort(1).withTol(10).drive(2150);
  chassis.withTurnPD(1.1,1).withTurnDirection(LEFT).justPD(1).withTol(1).turn(148).waitUntilSettled();
  chassis.withPD(0.2,1).withSlew(120).withHeading(148).autoSort(1).withDist(45).withTol(10).drive(1600);
  intake.middleSpinVelocity(-600);
  pros::delay(100);
  // intake.justOneBall(1).goalSort(REDBALL, 90, HOLDBALL);
  chassis.withPD(0.2,1).withSlew(50).withHeading(95).withTol(10).drive(-325);
  //Goal 8 (H)
  //Goal 9
  // Goal 8 Middle
` `
  chassis.withPD(0.4,0.001).withSlew(1).withHeading(135).drive(-1000);
  chassis.withTurnPD(1,1).withTurnSlew(1).withTurnDirection(LEFT).justPD(1).turn(315).waitUntilSettled();
  chassis.withPD(0.4,0.001).withSlew(1).withHeading(315).autoSort(1).drive(2000);
  intake.indexerSpinVelocity(200);
  //Goal 9 (E)
*/

  return *this;
}

Auton& Auton::runTests(){
              // chassis.withPD(0.6,1.175).withSlew(450).withHeading(350,1).autoSort(1).withTol(25).drive(1000).waitUntilSettled(0);
          // chassis.withPD(1.75,1).withSlew(350).withHeading(350,.1).withTol(10).withDist(80).driveCurve(1000,1,.075);
          chassis.autoSort(1).withSlop(1000, 3).withTurn(350, 133, 0.018, 66).move(5, 0.3, 0.01, 0.15);
  // chassis.setState(HOLD);
  // chassis.withSlop(10000, 1).withTurn(10, 133, 0, 66).move(57, .1, 0.001, 0.03).waitUntilSettled(0);
  // pros::delay(100);
  // chassis.withSlop(1000, 10).withTurn(0, 133, .001, 66).move(-16, .3, 0, .15).waitUntilSettled();
  // // // pros::delay(100);
  // chassis.withSlop(1000, 10).withTurn(325, 266, .001, 66).move(16, .3, 0.01, .15).waitUntilSettled();
  // chassis.withTurnPD(3,2).justPD(1).withTol(1).turn(180).waitUntilSettled();
  // chassis.withTurnPD(3,2).justPD(1).withTol(1).turn(0).waitUntilSettled();


  // chassis.withTurnPD(4,2).justPD(1).withTol(1).turn(280).waitUntilSettled();
  // chassis.withPD(.3,1).withSlew(175).withHeading(145,.25).withTol(10).driveCurve(-850, .3, .001);
  // motionProfile.calculate(10, 1);
  // motionProfile.drive();
  // intake.deploy();
  // intake.intakeSpin(12000);
  // chassis.withPD(.5,.65).withSlew(600).withHeading(0,.25).withTol(10).drive(1800);
  // chassis.withTurnPD(3,0.25).justPD(1).justOneSide(1).withTol(1).turn(270).waitUntilSettled();
  // chassis.withPD(.5,.001).withSlew(.25).withHeading(270,1).withTol(10).drive(-600);
  // chassis.withTurnPD(3,0.1).justPD(1).justOneSide(1).withTol(1).turn(230).waitUntilSettled();
  // chassis.withPD(1,.1).withSlew(.75).withHeading(225,50).withDist(150).withTol(10).drive(3000);
  // intake.intakeStop();
  // intake.middleSpin(12000);
  // intake.indexerSpin(12000);
  // pros::delay(700);
  // intake.middleStop();
  // intake.indexerStop();
  // chassis.driveDistAway(550);
  // // intake.intakeSpin(12000);
  // chassis.withTurnPD(2.5,0.25).justPD(1).justOneSide(1).withTol(1).turn(90).waitUntilSettled();
  // chassis.withPD(.5,.1).withSlew(.75).withHeading(90,1).withTol(10).drive(1800);
  // chassis.withTurnPD(3,0.25).justPD(1).justOneSide(1).withTol(1).turn(180).waitUntilSettled();
  // intake.intakeStop();
  // chassis.withPD(1,.1).withSlew(.75).withHeading(90,1).withDist(150).withTol(10).drive(2500);
  // intake.middleSpin(12000);
  // intake.indexerSpin(12000);


  // intake.intakeSpin(-8000);
  // intake.intakeStop();
  // intake.middleSpin(12000);
  // intake.indexerSpin(12000);
  // pros::delay(700);


  // intake.goalSort(alliance, 70, HOLDBALL);
  // intake.justOneBall(0).goalSort(REDBALL, 1000, HOLDBALL);
  // intake.indexerSpin(200);
  // pros::delay(200);
  // chassis.withPD(0.2,2).withSlew(200).withHeading(0).autoSort(1).withTol(10).drive(2300);
  // chassis.withPD(0.2,2).withSlew(200).withHeading(0).autoSort(1).withTol(10).drive(-350);
  // chassis.withTurnPD(.5,0.1).withTurnDirection(RIGHT).justPD(1).withTol(1).turn(45).waitUntilSettled();
  // chassis.withPD(0.2,2).withSlew(200).withHeading(45).withDist(50).withTol(10).drive(1000);
  // intake.goalSort(REDBALL, 70);
  //
  // chassis.driveDistAway(250);
  // chassis.withTurnPD(.5,0.1).withTurnDirection(RIGHT).justPD(1).withTol(1).turn(90).waitUntilSettled();
  // chassis.withPD(0.2,2).withSlew(200).withHeading(90).withTol(10).drive(2500);
  // chassis.withTurnPD(.5,0.1).withTurnDirection(LEFT).justPD(1).withTol(1).turn(45).waitUntilSettled();
  // chassis.withPD(0.2,2).withSlew(200).withHeading(45).withDist(45).withTol(50).drive(2500);
  // intake.goalSort(REDBALL, 150);
  // chassis.driveDistAway(200);

  // intake.goalSort(REDBALL, 100, SHOOTBALL);
  // chassis.driveDistAway(500);
  // pros::delay(10000);
  // chassis.withPD(0.2,1).withSlew(100).withHeading(290).autoSort(0).withDist(45).withTol(10).drive(1000);
  // intake.justOneBall(0).goalSort(REDBALL, 60, HOLDBALL);
  // chassis.driveDistAway(500);
  // intake.dropBall(EJECT);

  return *this;
}
