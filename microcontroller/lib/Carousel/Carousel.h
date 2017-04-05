#ifndef _CAROUSEL_H_
#define _CAROUSEL_H_

/* This class controls the carousel disk.
 * 
 * The setup method will automatically calibrate the position of the
 * stepper motor with the use of a light sensor.
 * 
 * After the carousel has been setup, other code can use this object
 * to access the slot objects and current angle of the carousel at
 * any given point in time.
 */

#include <Arduino.h>

#include "PeriodicTimer.h"
#include "Slot.h"
#include "LightSensor.h"
#include "StepperMotor.h"
#include "Angle.h"


class Carousel
{
  
  public:
  // the offset may need to be adjusted depending on lighting condtions
  Carousel(StepperMotor* motor, Angle origin_offset);
  
  Angle angle();
  Slot* first_slot(); // slot with the smallest start and end angle
  Slot* next_slot(Slot* slot); // in clockwise direction
  void setup();
  void start();
  
  private:
  
  static const StepperMotor::Direction _direction = StepperMotor::Direction::Forward;
  static const unsigned int _light_sensor_pin = A1;
  static const int _light_sensor_threshold = 500;
  static const float _speed; // rpm
  static const int _num_slots = 6;
  
  boolean _is_setup;
  LightSensor _light_sensor;
  StepperMotor* _motor;
  Angle _origin_offset;
  Slot _slots[_num_slots];
  
};

#endif
