#include "main.h"
#include "intakes.h"
#include "chassis.h"

static Intake intake;

bool Chassis::isSettled = true, Chassis::autoSort_enabled;
double Chassis::leftheading = L_IMU.get_heading(), Chassis::middleheading = M_IMU.get_heading(), Chassis::rightheading = R_IMU.get_heading(),
 Chassis::averageheading = (leftheading + middleheading + rightheading)/3;

double Chassis::power;
int Chassis::drive_theta;

double Chassis::kP_drive, Chassis::kD_drive, Chassis::kP_turn, Chassis::kD_turn;
int Chassis::direction_turn;

double Chassis::rate_drive, Chassis::rate_turn, Chassis::correction_rate;

int Chassis::output = 0;

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
  LEncoder.reset();
  REncoder.reset();
  pros::delay(3000);
}

void Chassis::odomReset() {
  REncoder.reset();
  LEncoder.reset();
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
  rate_drive = rate_;
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
    double error = abs(theta - averageheading);
    double prevError = error;
    double derivative = error - prevError;
    power = error*kP_turn + derivative*kD_turn;
    if(output < power) {
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
    if(autoSort_enabled){intake.autoSort(REDBALL);}
    double tpower = LF.get_target_velocity(); //Speed sent to motors
    double rpower = LF.get_actual_velocity(); //Actual speed of the motors
    if(leftheading > 355|| rightheading > 355 || middleheading > 355){
      averageheading = 0;
    } //Zeroes the average so it has a zero position
    printf("L_IMU, M_IMU, R_IMU,Average, TPower, RPower %f %f %f %f %d %f \n", leftheading, middleheading, rightheading, averageheading, output, power);
    if(averageheading >= theta-1 && averageheading <= theta+1){ //If it gets really close to the wanted angle it breaks the loop
      isSettled = true;
      LF.move(0);
      LB.move(0);
      RF.move(0);
      RB.move(0);
      if(autoSort_enabled){
      intake.intakeStop();
      intake.middleStop();
      intake.indexerStop();
      }
      break;
    }
  pros::delay(15);
  }
return *this;
}

Chassis& Chassis::drive(double target){
  odomReset();
  double leftvalue =LEncoder.get_value();
  double rightvalue =REncoder.get_value();
  printf("Left, Right %f %f  \n", leftvalue, rightvalue);
  isSettled = false;
  double averagePos = REncoder.get_value() + LEncoder.get_value()/2;
  while(target != averagePos) {
    double averagePos = REncoder.get_value() + LEncoder.get_value()/2;
    double error = target - averagePos;
    double prevError = error;
    double derivative = error - prevError;
    double power = error*kP_drive + derivative*kD_drive;
    if(output < power) {
      output += rate_drive;
    }else{
      output = power;
    }
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
    if(autoSort_enabled){intake.autoSort(REDBALL);}
    double leftvalue =LEncoder.get_value();
    double rightvalue =REncoder.get_value();
    printf("Error, AveragePos, LOutput, ROutput,Left, Right %f %f %f %f %f %f\n", error, averagePos, LOutput, ROutput,leftvalue, rightvalue);
    pros::delay(10);
    if(averagePos < target+50 && averagePos > target-50) {
      isSettled = true;
      LF.move(0);
      LB.move(0);
      RF.move(0);
      RB.move(0);
      if(autoSort_enabled){
      intake.intakeStop();
      intake.middleStop();
      intake.indexerStop();
      autoSort_enabled = false;
      }
      break;
    }
  }
return *this;
}
