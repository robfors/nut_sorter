#ifndef _SERVO_MOTOR_H_
#define _SERVO_MOTOR_H_

/* This class abstracts the functionality of a servo motor.
 * 
 */

#include <Arduino.h>
#include <Servo.h>

#include "CoterminalAngle.h"

class ServoMotor
{
  
  public:
  
  ServoMotor(int pin, CoterminalAngle inital_angle);
  
  void setup();
  void turn_to_angle(CoterminalAngle angle);
  
  private:
  
  CoterminalAngle _inital_angle;
  boolean _is_setup;
  int _pin;
  Servo _servo;
  
};

#endif
