#include "main.h"
#include "class/control/intakes.hpp"
#include "class/control/chassis.hpp"

static Intake intake;

bool Chassis::isSettled = true, Chassis::autoSort_enabled;
bool Chassis::justPID=false;
double Chassis::leftheading = L_IMU.get_heading(), Chassis::middleheading = M_IMU.get_heading(), Chassis::rightheading = R_IMU.get_heading(),
 Chassis::averageheading = (leftheading + middleheading + rightheading)/3;

double Chassis::power;
int Chassis::drive_theta;

double Chassis::kP_drive, Chassis::kD_drive, Chassis::kP_turn, Chassis::kD_turn;
int Chassis::direction_turn;

double Chassis::rate_drive, Chassis::rate_turn, Chassis::correction_rate;

double Chassis::output = 0;

int Chassis::slew_a = 200, Chassis::slew_x = 0;

double Chassis::distTarget;
bool Chassis::distSensorEnabled = false;

int Chassis::tol;

double Chassis::prevError = 0;

Chassis::Chassis() { }
Chassis::~Chassis() {
  reset();
}

void Chassis::reset() {
  LF.move_velocity(0);
  LB.move_velocity(0);
  RF.move_velocity(0);
  RB.move_velocity(0);
  LF.tare_position();
  LB.tare_position();
  RF.tare_position();
  RB.tare_position();
  L_IMU.reset();
  M_IMU.reset();
  R_IMU.reset();
  // LEncoder.reset();
  // REncoder.reset();
  LOdometer.reset();
  ROdometer.reset();
  ROdometer.set_reversed(1);
  pros::delay(3000);
}

void Chassis::odomReset() {
  // LEncoder.reset();
  // REncoder.reset();
  LOdometer.reset_position();
  ROdometer.reset_position();
  pros::delay(100);
}

void Chassis::waitUntilSettled() {
  while(!isSettled) pros::delay(20);
}

void Chassis::setState(int state_){
  switch (state_){
    case 1:{
      LF.set_brake_mode(MOTOR_BRAKE_HOLD);
      LB.set_brake_mode(MOTOR_BRAKE_HOLD);
      RF.set_brake_mode(MOTOR_BRAKE_HOLD);
      RB.set_brake_mode(MOTOR_BRAKE_HOLD);
      break;}
    case 2:{
      LF.set_brake_mode(MOTOR_BRAKE_COAST);
      LB.set_brake_mode(MOTOR_BRAKE_COAST);
      RF.set_brake_mode(MOTOR_BRAKE_COAST);
      RB.set_brake_mode(MOTOR_BRAKE_COAST);
      break;}
  }
}

Chassis& Chassis::withTurnSlew(double rate_){
  rate_turn = rate_;
  return *this;
}

Chassis& Chassis::withTurnPD(double kP_, double kD_){
  kP_turn = kP_;
  kD_turn = kD_;
  return *this;
}

Chassis& Chassis::withTurnDirection(int direction_turn_){
  direction_turn = direction_turn_;
  return *this;
}

Chassis& Chassis::autoSort(bool autoSort_enabled_){
  autoSort_enabled = autoSort_enabled_;
  return *this;
}

Chassis& Chassis::withSlew(double rate_){
  slew_a = rate_;
  return *this;
}

Chassis& Chassis::withPD(double kP_, double kD_){
  kP_drive = kP_;
  kD_drive = kD_;
  return *this;
}

Chassis& Chassis::withHeading(double drive_theta_, double correction_rate_){
  drive_theta = drive_theta_;
  correction_rate = correction_rate_;
  return *this;
}

Chassis& Chassis::justPD(bool justPD_){
  justPID = justPD_;
  return *this;
}

Chassis& Chassis::withDist(double distTarget_){
  distSensorEnabled = true;
  distTarget = distTarget_;
  return *this;
}

Chassis& Chassis::withTol(int tol_){
  tol = tol_;
  return *this;
}

Chassis& Chassis::turn(double theta_){
  isSettled = false;
  while(averageheading != theta_){
    double theta = theta_;
    leftheading = L_IMU.get_heading();
    middleheading = M_IMU.get_heading();
    rightheading = R_IMU.get_heading();
    averageheading = (leftheading + middleheading + rightheading)/3;
    if(leftheading > 355 || rightheading > 355 || middleheading > 355){
      if(direction_turn ==LEFT){ averageheading=360;}
      else{averageheading = 0;}
    }
    double error = fabs(theta - averageheading);
    double prevError = error;
    double derivative = error - prevError;
    power = error*kP_turn + derivative*kD_turn;
    if(output < power && !justPID) {
      output += rate_turn;
    }else{
      output = power;
    }
    switch (direction_turn){
      case LEFT: {
        LF.move_velocity(output);
        LB.move_velocity(output);
        RF.move_velocity(output);
        RB.move_velocity(output);
        break;}
      case RIGHT: {
        LF.move_velocity(-output);
        LB.move_velocity(-output);
        RF.move_velocity(-output);
        RB.move_velocity(-output);
        break;}
    }
    double tpower = LF.get_target_velocity(); //Speed sent to motors
    double rpower = LF.get_actual_velocity(); //Actual speed of the motors
    if(leftheading > 355|| rightheading > 355 || middleheading > 355){
      averageheading = 0;
    } //Zeroes the average so it has a zero position
    printf("L_IMU, M_IMU, R_IMU,Average, output, error %f %f %f %f %f %f \n", leftheading, middleheading, rightheading, averageheading, output, error);
    if(averageheading >= theta-tol && averageheading <= theta+tol){ //If it gets really close to the wanted angle it breaks the loop
      isSettled = true;
      justPID = false;
      LF.move(0);
      LB.move(0);
      RF.move(0);
      RB.move(0);
      break;
    }
  pros::delay(15);
  }
return *this;
}

Chassis& Chassis::drive(double target){
  odomReset();
  double leftvalue = LOdometer.get_position(); //LEncoder.get_value();
  double rightvalue =ROdometer.get_position();  //REncoder.get_value();
  printf("Left, Right %f %f  \n", leftvalue, rightvalue);
  isSettled = false;
  // double averagePos = (REncoder.get_value() + LEncoder.get_value())/2;
  while(1 == 1) {
    leftvalue = (LOdometer.get_position())/100; //LEncoder.get_value();
    rightvalue =(ROdometer.get_position())/100;  //REncoder.get_value();
    double averagePos = (leftvalue+rightvalue)/2;//(REncoder.get_value() + LEncoder.get_value())/2;
    double error = target - averagePos;
    double derivative = error - prevError;
    prevError = error;
    double power = error*kP_drive + derivative*kD_drive;

    if(output < power && !justPID){
      if(target>0)output = fabs(((-2*slew_a)/pow(M_E, (2.2*slew_x)/slew_a)+1)+slew_a);
      else{output = ((-2*slew_a)/pow(M_E, (2.2*slew_x)/slew_a)+1)+slew_a;}
    }else{
      output = power;
    }

    slew_x+=0.01;

    double LOutput = output;
    double ROutput = output;
    leftheading = L_IMU.get_heading();
    middleheading = M_IMU.get_heading();
    rightheading = R_IMU.get_heading();
    averageheading = (leftheading + middleheading + rightheading)/3;
    if(leftheading > 355 || rightheading > 355 || middleheading > 355){
      averageheading=0;
    }
    if( averageheading != drive_theta){ //Corrects the robot if it is straying from the wanted angle.
      int headDifference = drive_theta - averageheading;
      switch (drive_theta){
        case 0: {
          if(abs(headDifference) < 180){
            LOutput -=correction_rate;
            ROutput +=correction_rate;
          }else{
            LOutput +=correction_rate;
            ROutput -=correction_rate;
          }
          break;
        }
        default:{
          // if(headDifference < drive_theta){
          if(averageheading < drive_theta && averageheading!=0){
            LOutput +=correction_rate;
            ROutput -=correction_rate;
          }
          // else if(headDifference > drive_theta){
          else if(averageheading > drive_theta && averageheading!=0){
            LOutput -=correction_rate;
            ROutput +=correction_rate;
          }
          if(headDifference >180 && averageheading ==0){
            LOutput -=correction_rate;
            ROutput +=correction_rate;
          }else if(headDifference <180 && averageheading ==0){
            LOutput +=correction_rate;
            ROutput -=correction_rate;
          }
          break;
        }
      }
    }
    RF.move_velocity(ROutput);
    RB.move_velocity(ROutput);
    LF.move_velocity(-LOutput);
    LB.move_velocity(-LOutput);
    if(autoSort_enabled){
      switch(alliance){
        case 3:{intake.autoSort(REDBALL);} //If skills autosort as if Red Alliance.
        default:{intake.autoSort(alliance);}
      }
    }
    double leftvalue = LOdometer.get_position(); //LEncoder.get_value();
    double rightvalue = ROdometer.get_position(); //REncoder.get_value();
    printf("Error, AveragePos, LOutput, ROutput,Left, Right goalDist %f %f %f %f %f %f %f\n", error, averagePos, LOutput, ROutput,leftvalue, rightvalue,output);
    pros::delay(10);
    if(averagePos < target+tol && averagePos > target-tol) {
      LF.move(0);
      LB.move(0);
      RF.move(0);
      RB.move(0);
      odomReset();
      justPID = false;
      if(autoSort_enabled){
      intake.intakeStop();
      intake.middleStop();
      intake.indexerStop();
      autoSort_enabled = false;
      distSensorEnabled=false;
      }
      isSettled = true;
      break;
    }
    if(distSensorEnabled){
      if(goalDist.get() < distTarget && goalDist.get() != 0){
        distSensorEnabled=false;
        LF.move(0);
        LB.move(0);
        RF.move(0);
        RB.move(0);
        odomReset();
        justPID = false;
        if(autoSort_enabled){
        intake.intakeStop();
        intake.middleStop();
        intake.indexerStop();
        autoSort_enabled = false;
        }
        isSettled = true;
        break;
      }
    }
  }
return *this;
}

Chassis& Chassis::driveDistAway(double dist){
  isSettled = 0;
  while(!isSettled){
    LF.move_velocity(50);
    LB.move_velocity(50);
    RF.move_velocity(-50);
    RB.move_velocity(-50);
    if(goalDist.get() >= dist-5){
      LF.move(0);
      LB.move(0);
      RF.move(0);
      RB.move(0);
      break;
      isSettled = 1;
    }

  }
  return *this;
}
