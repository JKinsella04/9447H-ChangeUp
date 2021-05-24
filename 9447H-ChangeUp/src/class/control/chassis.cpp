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

double Chassis::output = 1;

int Chassis::slew_a = 600, Chassis::slew_x = 1;

double Chassis::distTarget;
bool Chassis::distSensorEnabled = false;

int Chassis::tol, Chassis::heading_diff;

double Chassis::prevError = 0;

bool Chassis::oneSide;

double Chassis::turnPrevError = 0;

bool Chassis::halt;
double Chassis:: m_error, m_integral, m_derivative, m_prevError, m_power, LOutput, ROutput, drive_tol = 10, turn_tol = 1,
                 t_error, t_integral, t_derivative, t_prevError, theta, turn_kP, turn,kI, turn_kD;

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
  while(L_IMU.is_calibrating() || M_IMU.is_calibrating() || R_IMU.is_calibrating()){
    pros::delay(5);
  }
}

void Chassis::odomReset() {
  // LEncoder.reset();
  // REncoder.reset();
  LOdometer.reset_position();
  ROdometer.reset_position();
  pros::delay(100);
}

// void Chassis::waitUntilSettled() {
//   while(!isSettled) pros::delay(20);
// }

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

void Chassis::stop(){
  distSensorEnabled=false;
  if(halt){
    LF.move(0);
    LB.move(0);
    RF.move(0);
    RB.move(0);
  }
  odomReset();
  justPID = false;
  if(autoSort_enabled){
  intake.intakeStop();
  intake.middleStop();
  intake.indexerStop();
  autoSort_enabled = false;
  }
  isSettled = true;
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

void Chassis::calcDir(int current_Pos, int target_Pos){
  heading_diff = current_Pos - target_Pos;
  if(currentPos == 0){
    if(abs(heading_diff) > 180) {direction_turn = LEFT;}
    else{direction_turn = RIGHT;}
    }
  if(heading_diff < 0){
    direction_turn = RIGHT;
    if(abs(heading_diff) > 180) direction_turn = LEFT;
  }
  if(heading_diff > 0){
    direction_turn = LEFT;
    if(abs(heading_diff) > 180) direction_turn = RIGHT;
  }
}

Chassis& Chassis::justOneSide(bool oneSide_){
  oneSide = oneSide_;
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
    calcDir(averageheading, theta_);
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
        RF.move_velocity(output);
        RB.move_velocity(output);
        LF.move_velocity(-output);
        LB.move_velocity(-output);
        break;}
      case RIGHT: {
        RF.move_velocity(-output);
        RB.move_velocity(-output);
        LF.move_velocity(output);
        LB.move_velocity(output);
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
      // if(target > 0){output += 5;}
      // else{output = output -= 5;}
    }else{
      output = power;
    }

    slew_x += 0.001;

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
            LOutput -= LOutput * correction_rate;
            ROutput += ROutput * correction_rate;
          }else{
            LOutput += LOutput * correction_rate;
            ROutput -= ROutput * correction_rate;
          }
          break;
        }
        default:{
          // if(headDifference < drive_theta){
          if(averageheading < drive_theta && averageheading!=0){
            LOutput += LOutput * correction_rate;
            ROutput -= ROutput * correction_rate;
          }
          // else if(headDifference > drive_theta){
          else if(averageheading > drive_theta && averageheading!=0){
            LOutput -= LOutput * correction_rate;
            ROutput += ROutput * correction_rate;
          }
          if(headDifference >180 && averageheading ==0){
            LOutput -= LOutput * correction_rate;
            ROutput += ROutput * correction_rate;
          }else if(headDifference <180 && averageheading ==0){
            LOutput += LOutput * correction_rate;
            ROutput -= ROutput * correction_rate;
          }
          break;
        }
      }
    }
    RF.move_velocity(ROutput);
    RB.move_velocity(ROutput);
    LF.move_velocity(LOutput);
    LB.move_velocity(LOutput);
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
      stop();
      break;
    }
    if(distSensorEnabled){
      if(ballIndexer.get() < distTarget &&  ballIndexer.get() != 0){
        stop();
        break;
      } else if(goalDist.get() < distTarget && goalDist.get() != 0){
        stop();
        break;
      }
    }
  }
return *this;
}

Chassis& Chassis::driveDistAway(double dist){
  isSettled = 0;
  while(!isSettled){
    LF.move_velocity(-150);
    LB.move_velocity(-150);
    RF.move_velocity(-150);
    RB.move_velocity(-150);
    if(goalDist.get() >= dist-5 || (ballIndexer.get() >= dist-5)){
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

Chassis& Chassis::driveCurve(double target, double turn_kP, double turn_kD){
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
      // if(target > 0){output += 5;}
      // else{output = output -= 5;}
    }else{
      output = power;
    }

    slew_x += 0.001;
    double LOutput = output;
    double ROutput = output;
    leftheading = L_IMU.get_heading();
    middleheading = M_IMU.get_heading();
    rightheading = R_IMU.get_heading();
    averageheading = (leftheading + middleheading + rightheading)/3;
    if(leftheading > 355 || rightheading > 355 || middleheading > 355){
      averageheading=0;
    }
    double heading_error = drive_theta - averageheading;
    if(fabs(heading_error) >= 3){ //Corrects the robot if it is straying from the wanted angle.
      calcDir(averageheading, drive_theta);
      double turnError = drive_theta - averageheading;
      double derivative = turnError - turnPrevError;
      turnPrevError = error;
      power = error*turn_kP + derivative*turn_kD;
      switch(direction_turn){
        case LEFT:{
            LOutput += power;
            ROutput -= power;
            break;
        }
        case RIGHT:{
            LOutput -= power;
            ROutput += power;
            break;
        }
      }
    }

    RF.move_velocity(ROutput);
    RB.move_velocity(ROutput);
    LF.move_velocity(LOutput);
    LB.move_velocity(LOutput);
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
      stop();
      break;
    }
    if(distSensorEnabled){
      if(ballIndexer.get() < distTarget &&  ballIndexer.get() != 0){
        stop();
        break;
      } else if(goalDist.get() < distTarget && goalDist.get() != 0){
        stop();
        break;
      }
    }
  }
return *this;
}

/*
Need
- Tol setter
- slew acceleration
*/

void Chassis::waitUntilSettled(bool halt_){
  halt = halt_;
}

Chassis& Chassis::withTurn(double theta_, double turn_kP_, double turn_kI_, double turn_kD_){
  theta = theta_;
  turn_kP = turn_kP_;
  turn_kI = turn_kI_;
  turn_kD = turn_kD_;
  return *this;
}

Chassis& Chassis::move(double target, double drive_kP, double drive_kI, double drive_kD){
  while(!isSettled){
  // Lateral mvmt PID calc.
  double current_Left = ( LOdometer.get_position() )/36000; //Convert from centidegress to degrees.
  double current_Right = ( ROdometer.get_position() )/36000;
  //Convert to distance traveled in inches.
  current_Left *= CIRCUMFERENCE;
  current_Right *= CIRCUMFERENCE;
  double averagePos = ( current_Left + current_Right ) /2;

  m_error = target - averagePos;
  m_integral += m_error;
  if(m_error == 0){
    m_integral = 0;
  }
  if(m_integral > 12000){
    m_integral = 120000;
  }
  m_derivative = m_error - m_prevError;
  m_prevError = m_error;
  m_power = m_error * drive_kP + m_integral * drive_kI + m_derivative * drive_kD;
  LOutput = m_power;
  ROutput = m_power;

  // Turn mvmt PID calc.
  leftheading = L_IMU.get_heading();
  middleheading = M_IMU.get_heading();
  rightheading = R_IMU.get_heading();
  averageheading = (leftheading + middleheading + rightheading)/3;
  if(leftheading > 355 || rightheading > 355 || middleheading > 355){
    if(direction_turn ==LEFT){ averageheading=360;}
    else{averageheading = 0;}
  }
  t_error = theta - averageheading;
  t_integral += t_error;
  if(t_error == 0){
    t_integral = 0;
  }
  if(t_integral > 12000){
    t_integral = 120000;
  }
  t_derivative = t_error - t_prevError;
  t_prevError = t_error;
  turn_output = t_error * turn_kP + t_integral * turn_kI + t_derivative * turn_kD;

  calcDir(averageheading, drive_theta);
  switch(direction_turn){
    case LEFT:{
        LOutput += turn_output;
        ROutput -= turn_output;
        break;
    }
    case RIGHT:{
        LOutput -= turn_output;
        ROutput += turn_output;
        break;
    }
  }

  LF.move_voltage(LOutput);
  LB.move_voltage(LOutput);
  RF.move_voltage(ROutput);
  RB.move_voltage(ROutput);

  if(fabs(m_error) < drive_tol && fabs(t_error) < turn_tol){
    stop();
    break;
    }
  pros::delay(2);
  }
  return *this;
}
