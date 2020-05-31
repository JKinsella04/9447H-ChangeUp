#include "main.h"

#include "class/control/chassis.h"




void autonomous() {
  Chassis chassis;
  chassis.reset();
  // chassis.turn(90,4.7,.1).Slew(5);
  chassis.withPD(0.075,0.001).withSlew(2).drive(3150).waitUntilSettled();
  chassis.withTurnPD(2.7,.1).withTurnSlew(2).turn(90).waitUntilSettled();//90
  // chassis.withPD(0.075,0.001).withSlew(2).drive(4150).waitUntilSettled();

}
