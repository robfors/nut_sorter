#ifndef _CHUTE_H_
#define _CHUTE_H_

/* This object will simply turn the chute to the requested cup.
 * 
 * The angles for each cup is defined in the turn_to_cup_for method.
 */

#include <Arduino.h>

#include "Angle.h"
#include "Servo.h"

class Chute
{
  
  public:
  
  enum  class ObjectType { Coin, SmallSteelNut, SmallBrassNut, BigBrassNut, BigNylonNut, Empty };
  
  Chute();
  
  void setup();
  void turn_to_cup_for(ObjectType object_type);
  
  private:
  
  static Angle _inital_angle;
  
  boolean _is_setup;
  Servo _servo;
  
};

#endif
