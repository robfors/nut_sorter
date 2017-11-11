#ifndef _NUT_SORTER_CHUTE_H_
#define _NUT_SORTER_CHUTE_H_

/* This object will simply turn the chute to the requested cup.
 * 
 * The angles for each cup is defined in the turn_to_cup_for method.
 */


namespace NutSorter
{
  
  class Chute
  {
    
    public:
    
    enum class ObjectType { Coin, SmallSteelNut, SmallBrassNut, BigBrassNut, BigNylonNut, Empty };
    
    static void turn_to_cup_for(ObjectType object_type);
    
    private:
    
    
  };
  
}

#endif
