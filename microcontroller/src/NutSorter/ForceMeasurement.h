#ifndef _NUT_SORTER_FORCE_MEASUREMENT_H_
#define _NUT_SORTER_FORCE_MEASUREMENT_H_

/* This class defines the a measurment task.
 * 
 * Use this by first calling 'setup'.
 * Then call 'tick' as offten as posible to ensure we meet the deadlines.
 * 
 * Every time we call 'tick' it will check if a slot is over the sensor.
 * If so it will then check is the slot has moved 1mm since the last
 * measurment.
 * If so it will then make a measurment and save the result to the slot's
 * measurment variables.
 */


namespace NutSorter
{
  
  class ForceMeasurement
  {
    
    public:
    
    static void tick();
    
    private:
    
    static Slot* _current_slot;
    static CoterminalAngle _end_angle;
    static int _distance_at_last_measurement;
    static CoterminalAngle _start_angle;
    static boolean _was_slot_over_sensor;
    
    static void _finish_with_slot(boolean has_heavy_object);
    static boolean _is_slot_over_sensor();
    
  };
  
}

#endif
