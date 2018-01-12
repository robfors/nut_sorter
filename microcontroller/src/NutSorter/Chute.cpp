#include "NutSorter.h"


namespace NutSorter
{
  
  //
  // public
  //
  
  
  void Chute::turn_to_cup_for(ObjectType object_type)
  {
  	ServoMotor* servo_motor = &Hardware::Main::chute_servo_motor;
    
    switch (object_type)
    {
      case ObjectType::Coin:
        servo_motor->turn_to_angle(CoterminalAngle(30.0));
        break;
      case ObjectType::SmallSteelNut:
        servo_motor->turn_to_angle(CoterminalAngle(175.0));
        break;
      case ObjectType::SmallBrassNut:
        servo_motor->turn_to_angle(CoterminalAngle(65.0));
        break;
      case ObjectType::BigBrassNut:
        servo_motor->turn_to_angle(CoterminalAngle(140.0));
        break;
      case ObjectType::BigNylonNut:
        servo_motor->turn_to_angle(CoterminalAngle(100.0));
        break;
      default:
        //ignore
        break;
    }
  }
  
  
  //
  // private
  //
  
}
