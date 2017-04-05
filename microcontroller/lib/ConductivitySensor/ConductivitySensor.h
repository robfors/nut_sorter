#ifndef _CONDUCTIVITY_SENSOR_H_
#define _CONDUCTIVITY_SENSOR_H_

/* 1- we set this up by specifying a array of pins.
 * 2- call setup
 * 3- when we want to make a measurment we call 'measure()'
 * 4- we repeatedly call is_result_ready() untill it returns true (we do
 *    this so the code can wait without blocking)
 * 5- call 'result()' to find out if a conductive material is present
 * repeat steps 3 to 5
 * 
 * 
 * This code works by seting up one of the pins as a current source (HIGH, with high impedance)
 * and setting the rest of the pins as a current sync (LOW, with low impedance).
 * We know a conductive material is present if the source pin's voltage is low.
 * The code will do this enough times to test for a connection between any two of the pins.
 * 
 */
 

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
