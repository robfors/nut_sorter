#ifndef _NUT_SORTER_INTERPRETER_H_
#define _NUT_SORTER_INTERPRETER_H_

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
 * This class reads a slot's measurment data as it get near the exit hole.
 * From this data is will determine what type of object it is and request
 * the chute to turn to the according cup.
 * 
 * The system's core sorting logic can be found in '_process_slot()'.
 */


namespace NutSorter
{
  
  class Interpreter
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
