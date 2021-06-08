#include "class/control/odom.hpp"

double Odom::global_x = 0, Odom::global_y = 0, Odom::distance = 0, Odom::leftheading = 0, Odom::middleheading = 0, Odom::rightheading = 0, Odom::averageheading = 0, Odom::lValue = 0, Odom::rValue = 0, Odom::leftChange = 0, Odom::rightChange = 0, Odom::lastLPos = 0, Odom::lastRPos = 0;

void Odom::updatePosition(){
  while(1){
    lValue = LOdometer.get_position(); //LEncoder.get_value();
    rValue = ROdometer.get_position();  //REncoder.get_value();
    // lValue = LOdometer.get_angle(); //LEncoder.get_value();
    // rValue = ROdometer.get_angle();  //REncoder.get_value();

    // Convert to distance in inches.
    lValue /= CONVERSION;
    rValue /= CONVERSION;

    // Get distance traveled between last position and now.
    leftChange = lValue - lastLPos;
    rightChange = rValue - lastRPos;
    // Average the change between both sides.
    distance = (leftChange + rightChange)/2;

    leftheading = L_IMU.get_heading();
    middleheading = M_IMU.get_heading();
    rightheading = R_IMU.get_heading();
    averageheading = (leftheading + middleheading + rightheading)/3;
    if(leftheading > 355 || rightheading > 355 || middleheading > 355)averageheading = 0;

    global_x += distance * cos(averageheading);
    global_y += distance * sin(averageheading);

    lastLPos += leftChange;
    lastRPos += rightChange;

    printf("X: %f Y: %f Theta: %f\n",  global_x, global_y, averageheading);
    // pros::lcd::print(1, "X, %f Y: %f, ", global_x, global_y);
    // pros::lcd::print(2, "H: %f D: %f",averageheading, distance);
  pros::delay(5);
  }
}
