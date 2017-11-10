#ifndef _NUT_SORTER_CHUTE_H_
#define _NUT_SORTER_CHUTE_H_

/* This object will simply turn the chute to the requested cup.
 * 
 * The angles for each cup is defined in the turn_to_cup_for method.
 */

#include <Arduino.h>

#include "CoterminalAngle.h"
#include <Servo.h>

namespace NutSorter
{
  
  class Chute
  {
    
    public:
    
    enum class ObjectType { Coin, SmallSteelNut, SmallBrassNut, BigBrassNut, BigNylonNut, Empty };
    
    Chute();
    
    void setup();
    void turn_to_cup_for(ObjectType object_type);
    
    private:
    
    static CoterminalAngle _inital_angle;
    
    boolean _is_setup;
    Servo _servo;
    
  };
  
}

#endif