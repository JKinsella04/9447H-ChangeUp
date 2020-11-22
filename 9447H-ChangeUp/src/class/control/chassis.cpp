#include "main.h"
#include "chassis.h"

bool Chassis::isSettled = true;
double Chassis::leftheading = L_IMU.get_heading(), Chassis::middleheading = M_IMU.get_heading(), Chassis::rightheading = R_IMU.get_heading(),
 Chassis::averageheading = (leftheading + middleheading + rightheading)/3;

double Chassis::power, Chassis::drive_theta=0;

double Chassis::kP_drive, Chassis::kD_drive, Chassis::kP_turn, Chassis::kD_turn;
int Chassis::direction_turn;

double Chassis::rate_drive, Chassis::rate_turn;

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

Chassis& Chassis::withSlew(double rate_){
  rate_drive = rate_;
  return *this;
}

Chassis& Chassis::withPD(double kP_, double kD_){
  kP_drive = kP_;
  kD_drive = kD_;
  return *this;
}

Chassis& Chassis::withHeading(double drive_theta_){
  drive_theta = drive_theta_;
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
          if(leftheading > 355|| rightheading > 355 || middleheading > 355){
            if(direction_turn ==LEFT){ averageheading=360;}
            else{averageheading = 0;}  
          }
          double error = theta - averageheading;
          double prevError = error;
          double derivative = error - prevError;
          power = error*kP_turn + derivative*kD_turn;
          // if (output <= power) {
          //   output += rate_turn;
          // }else if(output >= power){
          //   output -= rate_turn;
          // }
          switch (direction_turn){
            case LEFT: {
              LF.move_velocity(abs(power));
              LB.move_velocity(abs(power));
              RF.move_velocity(abs(power));
              RB.move_velocity(abs(power));
            break;}
            case RIGHT: {
              LF.move_velocity(-power);
              LB.move_velocity(-power);
              RF.move_velocity(-power);
              RB.move_velocity(-power);
            break;}
          }
          double tpower = LF.get_target_velocity(); //Speed sent to motors
          double rpower = LF.get_actual_velocity(); //Actual speed of the motors
          if(leftheading > 355|| rightheading > 355 || middleheading > 355){
            averageheading = 0;
          } //Zeroes the average so it has a zero position
          printf("L_IMU, M_IMU, R_IMU,Average, TPower, RPower %f %f %f %f %f %f \n", leftheading, middleheading, rightheading, averageheading, tpower, rpower);
          if(averageheading >= theta-5 && averageheading <= theta+5){ //If it gets really close to the wanted angle it breaks the loop
            isSettled = true;
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
    double leftvalue =LEncoder.get_value();
    double rightvalue =REncoder.get_value();
    printf("Left, Right %f %f  \n", leftvalue, rightvalue);
    // pros::delay(1000);
    isSettled = false;
    double averagePos = REncoder.get_value() + LEncoder.get_value()/2;
    while(target != averagePos) {
      double averagePos = REncoder.get_value() + LEncoder.get_value()/2;
      double error = target - averagePos;
      double prevError = error;
      double derivative = error - prevError;
      double power = error*kP_drive + derivative*kD_drive;
      if(output <= power + rate_drive) {
        output += rate_drive;
      }else if(output >= power){
        output -= rate_drive;
      }
      double LOutput = output;
      double ROutput = output;
      // leftheading = L_IMU.get_heading();
      // middleheading = M_IMU.get_heading();
      // rightheading = R_IMU.get_heading();
      // averageheading = (leftheading + middleheading + rightheading)/3;
      // if( averageheading != drive_theta){
      //   double headDifference = drive_theta - averageheading;
      //   // if(abs(headDifference) < 180){
      //   //   LOutput = LOutput -5;
      //   //   ROutput = ROutput +5;
      //   // }else{
      //   //   ROutput = ROutput -5;
      //   //   LOutput = LOutput -5;
      //   // }
      // }
      RF.move(ROutput);
      RB.move(ROutput);
      LF.move(-LOutput);
      LB.move(-LOutput);
      double leftvalue =LEncoder.get_value();
      double rightvalue =REncoder.get_value();
      printf("Error, AveragePos, Left, Right %f %f %f %f \n", error, averagePos, leftvalue, rightvalue);
      pros::delay(10);
      if(averagePos < target+50 && averagePos > target-50) {
        isSettled = true;
        LF.move(0);
        LB.move(0);
        RF.move(0);
        RB.move(0);
        break;
      }
    }
    return *this;
  }
