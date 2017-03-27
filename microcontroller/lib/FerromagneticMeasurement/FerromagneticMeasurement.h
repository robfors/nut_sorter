#ifndef _FERROMAGNETIC_MEASUREMENT_H_
#define _FERROMAGNETIC_MEASUREMENT_H_

#include <Arduino.h>

#include "FerromagneticSensor.h"
#include "Slot.h"
#include "Disk.h"
#include "Angle.h"


class FerromagneticMeasurement
{
  
  public:
  
  FerromagneticMeasurement(Disk* disk, Angle start_angle, Angle end_angle);
  
  void setup();
  void tick();
  
  private:
  
  Slot* _current_slot;
  Disk* _disk;
  Angle _end_angle;
  int _distance_at_last_measurement;
  FerromagneticSensor _sensor;
  Angle _start_angle;
  boolean _is_setup;
  boolean _was_slot_over_sensor;
  
  void _finish_with_slot(boolean has_ferromagnetic_object);
  boolean _is_slot_over_sensor();
  
};

#endif
