#ifndef _INTERPRETER_H_
#define _INTERPRETER_H_

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

#include <Arduino.h>

#include "Slot.h"
#include "Carousel.h"
#include "Chute.h"
#include "Profile.h"


class Interpreter
{
  
  public:
  
  Interpreter(Carousel* carousel, Chute* chute, Angle start_angle);
  
  void setup();
  void tick();
  
  private:
  
  Chute* _chute;
  Slot* _next_slot;
  Carousel* _carousel;
  Angle _start_angle;
  boolean _is_setup;
  
  void _process_slot(Slot* slot);
  
};

#endif
