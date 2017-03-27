#include "Servo.h"


//
// public
//


Servo::Servo(int pin, Angle inital_angle)
{
  _pin = pin;
  _inital_angle = inital_angle;
  _is_setup = false;
}


void Servo::setup()
{
  _var_speed_servo.attach(_pin);
  _var_speed_servo.slowmove(_inital_angle.to_degrees(), 1);
  
  _is_setup = true;
}


void Servo::turn_to_angle(Angle angle)
{
	if (!_is_setup)
	  return;
  
  _var_speed_servo.write(angle.to_degrees());
}


//
// private
//
