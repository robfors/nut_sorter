#include "NutSorter.h"


namespace NutSorter
{
  
  //
  // public
  //
  
  
  void Chute::turn_to_cup_for(ObjectType object_type)
  {
  	Servo* servo = &Hardware::Main::chute_servo;
    
    switch (object_type)
    {
      case ObjectType::Coin:
        servo->turn_to_angle(CoterminalAngle(30.0));
        break;
      case ObjectType::SmallSteelNut:
        servo->turn_to_angle(CoterminalAngle(175.0));
        break;
      case ObjectType::SmallBrassNut:
        servo->turn_to_angle(CoterminalAngle(65.0));
        break;
      case ObjectType::BigBrassNut:
        servo->turn_to_angle(CoterminalAngle(140.0));
        break;
      case ObjectType::BigNylonNut:
        servo->turn_to_angle(CoterminalAngle(100.0));
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
