#ifndef _FORCE_MEASUREMENT_H_
#define _FORCE_MEASUREMENT_H_

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

#include <Arduino.h>

#include "ForceSensor.h"
#include "Slot.h"
#include "Carousel.h"
#include "Angle.h"


class ForceMeasurement
{
  
  public:
  
  ForceMeasurement(Carousel* carousel, Angle start_angle, Angle end_angle);
  
  void setup();
  void tick();
  
  private:
  
  static const int _pin = 0;
  
  Slot* _current_slot;
  Carousel* _carousel;
  Angle _end_angle;
  int _distance_at_last_measurement;
  ForceSensor _sensor;
  Angle _start_angle;
  boolean _is_setup;
  boolean _was_slot_over_sensor;
  
  void _finish_with_slot(boolean has_heavy_object);
  boolean _is_slot_over_sensor();
  
};

#endif
