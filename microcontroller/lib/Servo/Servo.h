#ifndef _SERVO_H_
#define _SERVO_H_

#include <Arduino.h>

#include "VarSpeedServo.h" 
#include "Angle.h"

class Servo
{
  
  public:
  
  Servo(int _pin, Angle inital_angle);
  
  void setup();
  void turn_to_angle(Angle angle);
  
  private:
  
  Angle _inital_angle;
  boolean _is_setup;
  int _pin;
  VarSpeedServo _var_speed_servo;
  
};

#endif
