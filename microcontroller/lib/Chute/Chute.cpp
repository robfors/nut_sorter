#include "Chute.h"

Angle Chute::_inital_angle = Angle(90.0);

//
// public
//


Chute::Chute()
  : _servo(9, _inital_angle)
{
  _is_setup = false;
}


void Chute::setup()
{
  _servo.setup();
  
  _is_setup = true;
}


void Chute::turn_to_cup_for(ObjectType object_type)
{
	if (!_is_setup)
	  return;
  
  switch (object_type)
  {
  case ObjectType::Coin:
    _servo.turn_to_angle(Angle(30.0));
    break;
  case ObjectType::SmallSteelNut:
    _servo.turn_to_angle(Angle(175.0));
    break;
  case ObjectType::SmallBrassNut:
    _servo.turn_to_angle(Angle(65.0));
    break;
  case ObjectType::BigBrassNut:
    _servo.turn_to_angle(Angle(140.0));
    break;
  case ObjectType::BigNylonNut:
    _servo.turn_to_angle(Angle(100.0));
    break;
  }
}


//
// private
//
