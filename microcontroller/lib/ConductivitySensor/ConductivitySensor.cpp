#include "ConductivitySensor.h"


//
// public
//


ConductivitySensor::ConductivitySensor(int pins[], int wire_count)
: _propagation_timer(_propagation_delay, Timer::Units::Milliseconds)
{
  _is_setup = false;
  _last_pin_change_time = 0;
  _is_measurement_pending = false;
  _is_measurement_result_ready = false;
  _pins = pins;
  _source_wire_index = -1;
  _wire_count = wire_count;
}


void ConductivitySensor::measure()
{
  if (!_is_setup)
    return;
  if (_is_measurement_pending)
    return;
    
  _is_measurement_pending = true;
  _source_wire_index = 0;
  _activate_wire(_source_wire_index);
}


boolean ConductivitySensor::is_result_ready()
{
  return _is_measurement_result_ready;
}


boolean ConductivitySensor::result()
{
  if (!is_result_ready())
    return false;
  
  _is_measurement_result_ready = false;
  return _measurement_result;
}


boolean ConductivitySensor::setup()
{
  if(_wire_count < 2)
    return false;
  
  // setup pins
  for (int pin_index = 0; pin_index < _wire_count; pin_index++)
    _deactivate_wire(pin_index);
  
  // test wires
  
  for (int source_wire_index = 0; source_wire_index < _wire_count; source_wire_index++)
  {
    int source_pin = _pins[source_wire_index];
    _activate_wire(source_wire_index);
    delay(_propagation_delay);
    if (digitalRead(source_pin) == LOW)
      return false;
    if (!_are_all_pins_low(source_pin))
      return false;
    _deactivate_wire(source_wire_index);
    delay(_propagation_delay);
  }
  
  for (int sync_wire_index = 0; sync_wire_index < _wire_count; sync_wire_index++)
  {
    int sync_pin = _pins[sync_wire_index];
    if (digitalRead(sync_pin) == HIGH)
      return false;
  }
  
  _is_setup = true;
  
  return true;
}


void ConductivitySensor::tick()
{
  if (_is_measurement_pending && _propagation_timer.is_complete())
  {
    int source_pin = _pins[_source_wire_index];
    
    boolean pin_state = digitalRead(source_pin);
    _deactivate_wire(_source_wire_index);
    
    if (pin_state == LOW)
    {
      _end_measurement(true);
      return;
    }
		
    _source_wire_index++;
    if (_source_wire_index >= _wire_count)
    {
      _end_measurement(false);
      return;
    }
    
    _activate_wire(_source_wire_index);
  }
}


//
// private
//

void ConductivitySensor::_activate_wire(int wire_index)
{
  int source_pin = _pins[wire_index];
  pinMode(source_pin, INPUT_PULLUP);
  _propagation_timer.start();
}


boolean ConductivitySensor::_are_all_pins_low(int exclude_pin)
{
	for (int pin_index = 0; pin_index < _wire_count; pin_index++)
  {
    int pin = _pins[pin_index];
    if (pin == exclude_pin)
      continue;
    if (digitalRead(pin) == HIGH)
      return false;
  }
  return true;
}


void ConductivitySensor::_deactivate_wire(int wire_index)
{
  int source_pin = _pins[wire_index];
  digitalWrite(source_pin, LOW);
  pinMode(source_pin, OUTPUT);
}


void ConductivitySensor::_end_measurement(boolean result)
{
  _is_measurement_result_ready = true;
  _measurement_result = result;
  _is_measurement_pending = false;
}
