#ifndef _NUT_SORTER_CAROUSEL_H_
#define _NUT_SORTER_CAROUSEL_H_

/* This class controls the carousel disk.
 * 
 * The setup method will automatically calibrate the position of the
 * stepper motor with the use of a light sensor.
 * 
 * After the carousel has been setup, other code can use this object
 * to access the slot objects and current angle of the carousel at
 * any given point in time.
 */


namespace NutSorter
{
  
  class Carousel
  {
    
    public:
    
    static CoterminalAngle angle();
    static Slot* first_slot(); // slot with the smallest start and end angle
    static Slot* next_slot(Slot* slot); // in clockwise direction
    static void setup();
    static void start();
    
    private:
    
    static StepperMotor::Direction _direction;
    static float _speed; // rpm
    static CoterminalAngle _origin_offset;
    static boolean _is_setup;
    static Slot _slots[];
    
    static StepperMotor* _motor();
    static int _slot_count();
    
  };
  
}

#endif
