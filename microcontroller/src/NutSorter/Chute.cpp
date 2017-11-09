#include "Chute.h"


CoterminalAngle NutSorter::Chute::_inital_angle = CoterminalAngle(90.0);


//
// public
//


NutSorter::Chute::Chute()
  : _servo(9, _inital_angle)
{
  _is_setup = false;
}


void NutSorter::Chute::setup()
{
  _servo.setup();
  
  _is_setup = true;
}


void NutSorter::Chute::turn_to_cup_for(ObjectType object_type)
{
	if (!_is_setup)
	  return;
  
  switch (object_type)
  {
  case ObjectType::Coin:
    _servo.turn_to_angle(CoterminalAngle(30.0));
    break;
  case ObjectType::SmallSteelNut:
    _servo.turn_to_angle(CoterminalAngle(175.0));
    break;
  case ObjectType::SmallBrassNut:
    _servo.turn_to_angle(CoterminalAngle(65.0));
    break;
  case ObjectType::BigBrassNut:
    _servo.turn_to_angle(CoterminalAngle(140.0));
    break;
  case ObjectType::BigNylonNut:
    _servo.turn_to_angle(CoterminalAngle(100.0));
    break;
  }
}


//
// private
//
