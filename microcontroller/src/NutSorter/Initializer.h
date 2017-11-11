#ifndef _NUT_SORTER_INITIALIZER_H_
#define _NUT_SORTER_INITIALIZER_H_

/* This class defines the a task.
 * 
 * Use this by first calling 'setup'.
 * Then call 'tick' as offten as posible to ensure we meet the deadlines.
 * 
 * Every time we call 'tick' it will check if a slot is over the sensor.
 * If so it will then check is the slot has moved 1mm since the last
 * measurment.
 * If so it will then make a measurment and save the result to the slot's
 * measurment variables.
 * 
 * This class just resets a slot's state around the same time as a new
 * object is being placed in it.
 */


namespace NutSorter
{
  
  class Initializer
  {
    
    public:
    
    static void tick();
    
    private:
    
    static Slot* _next_slot;
    static CoterminalAngle _start_angle;
    
    static void _process_slot(Slot* slot);
    
  };
  
}

#endif
