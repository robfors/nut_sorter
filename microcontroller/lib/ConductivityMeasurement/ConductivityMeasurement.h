#ifndef _CONDUCTIVITY_MEASUREMENT_H_
#define _CONDUCTIVITY_MEASUREMENT_H_

#include <Arduino.h>

#include "ConductivitySensor.h"
#include "Slot.h"
#include "Disk.h"
#include "Angle.h"


class ConductivityMeasurement
{
  
  public:
  
  ConductivityMeasurement(Disk* disk, Angle start_angle, Angle end_angle);
  
  boolean setup();
  void tick();
  
  private:
  
  static int _sensor_pins[3];
  static const int _sensor_wire_count = 3;
  
  Slot* _current_slot;
  Disk* _disk;
  Angle _end_angle;
  int _distance_at_last_measurement;
  ConductivitySensor _sensor;
  Angle _start_angle;
  boolean _is_setup;
  boolean _was_slot_over_sensor;
  
  void _finish_with_slot(boolean has_ferromagnetic_object);
  boolean _is_slot_over_sensor();
  
};

#endif
