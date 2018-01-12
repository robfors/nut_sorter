#include "ServoMotor.h"


//
// public
//


ServoMotor::ServoMotor(int pin, CoterminalAngle inital_angle)
{
  _pin = pin;
  _inital_angle = inital_angle;
  _is_setup = false;
}


void ServoMotor::setup()
{
  _servo.attach(_pin);
  _servo.write(_inital_angle.to_degrees());
  
  _is_setup = true;
}


void ServoMotor::turn_to_angle(CoterminalAngle angle)
{
	if (!_is_setup)
	  return;
  
  _servo.write(angle.to_degrees());
}


//
// private
//
