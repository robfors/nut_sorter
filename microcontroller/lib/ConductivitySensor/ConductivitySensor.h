#ifndef _CONDUCTIVITY_SENSOR_H_
#define _CONDUCTIVITY_SENSOR_H_

#include <Arduino.h>

#include "Timer.h"

class ConductivitySensor
{
  
  public:
  
  ConductivitySensor(int pins[], int wire_count);
  
  void measure();
  boolean is_result_ready();
  boolean result();
  boolean setup();
  void tick();
  
  private:
  
  static const int _propagation_delay = 100; // ms
  
  boolean _is_setup;
  unsigned long _last_pin_change_time;
  boolean _is_measurement_pending;
  boolean _is_measurement_result_ready;
  boolean _measurement_result;
  int* _pins;
  Timer _propagation_timer;
  int _source_wire_index;
  int _wire_count;
  
  void _activate_wire(int wire_index);
  boolean _are_all_pins_low(int exclude_pin); 
  void _deactivate_wire(int wire_index);
  void _end_measurement(boolean result);
  
};

#endif
