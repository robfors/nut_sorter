#ifndef _PROFILE_MEASUREMENT_H_
#define _PROFILE_MEASUREMENT_H_

#include <Arduino.h>

#include "LightSensor.h"
#include "Slot.h"
#include "Disk.h"
#include "Angle.h"


class ProfileMeasurement
{
  
  public:
  
  ProfileMeasurement(Disk* disk, Angle start_angle, Angle end_angle);
  
  void setup();
  void tick();
  
  private:
  
  static const int _pin = A2;
  static const int _light_sensor_threshold = 200;
  
  Slot* _current_slot;
  Disk* _disk;
  Angle _end_angle;
  int _distance_at_last_measurement;
  LightSensor _sensor;
  Angle _start_angle;
  boolean _is_setup;
  boolean _was_slot_over_sensor;
  
  void _finish_with_slot();
  boolean _is_slot_over_sensor();
  
};

#endif
