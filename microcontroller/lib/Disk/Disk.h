#ifndef _DISK_H_
#define _DISK_H_

#include <Arduino.h>

#include "PeriodicTimer.h"
#include "Slot.h"
#include "LightSensor.h"
#include "StepperMotor.h"
#include "Angle.h"


class Disk
{
  
  public:
  
  Disk(StepperMotor* motor, Angle origin_offset);
  
  Angle angle();
  Slot* first_slot();
  Slot* next_slot(Slot* slot);
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
