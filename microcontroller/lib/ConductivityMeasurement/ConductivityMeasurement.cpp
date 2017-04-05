#include "ConductivityMeasurement.h"

int ConductivityMeasurement::_sensor_pins[] = {5, 6, 7};

//
// public
//


ConductivityMeasurement::ConductivityMeasurement(Carousel* carousel, Angle start_angle, Angle end_angle)
: _sensor(_sensor_pins, _sensor_wire_count)
{
  _end_angle = end_angle;
  _carousel = carousel;
  _current_slot = NULL;
  _distance_at_last_measurement = 0;
  _start_angle = start_angle;
  _is_setup = false;
  _was_slot_over_sensor = false;
}


boolean ConductivityMeasurement::setup()
{
  if (!_sensor.setup())
    return false;
  
  _current_slot = _carousel->first_slot();
  _was_slot_over_sensor = false;
  _is_setup = true;

  return true;
}


void ConductivityMeasurement::tick()
{
	if (!_is_setup)
	  return;
  
  _sensor.tick();
  
  if (!_was_slot_over_sensor)
  {
    if (_current_slot->is_over(_start_angle))
    {
      _current_slot->reset_odometer();
      _distance_at_last_measurement = 0;
      _was_slot_over_sensor = true;
    }
  }
  else
  {
  	if (!_is_slot_over_sensor())
    {
      _finish_with_slot(false);
      return;
    }
    
    if (_sensor.is_result_ready())
    {
      if (_sensor.result())
      {
        _finish_with_slot(true);
        return;
      }
    }
    
    int distance = (int)(_current_slot->odometer());
    
    if (distance >= _distance_at_last_measurement + 1)
    {
      _sensor.measure();
      _distance_at_last_measurement++;
    }
  }
  
}


//
// private
//


void ConductivityMeasurement::_finish_with_slot(boolean has_conductive_object)
{
  _current_slot->has_conductive_object = has_conductive_object;
  _current_slot = _carousel->next_slot(_current_slot);
  _was_slot_over_sensor = false;
}

boolean ConductivityMeasurement::_is_slot_over_sensor()
{
  return _current_slot->is_over(_start_angle, _end_angle);
}
