#ifndef _NUT_SORTER_FORCE_SENSOR_H_
#define _NUT_SORTER_FORCE_SENSOR_H_

/* This simple class reads a value from a specified analogue pin where
 * a force sensor is connected (after the amp curcit).
 */


namespace NutSorter
{
  
  class ForceSensor
  {
    
    public:
    
    ForceSensor(int pin);
    
    boolean is_depressed();
    void setup();
    
    private:
    
    static const int _threshold = 500;
    
    boolean _is_setup;
    int _pin;
    
    boolean _is_depressed();
    
  };
  
}

#endif
