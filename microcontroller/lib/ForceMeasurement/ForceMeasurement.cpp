#include "ForceMeasurement.h"


//
// public
//


ForceMeasurement::ForceMeasurement(Carousel* carousel, Angle start_angle, Angle end_angle)
: _sensor(_pin)
{
  _end_angle = end_angle;
  _carousel = carousel;
  _current_slot = NULL;
  _distance_at_last_measurement = 0;
  _start_angle = start_angle;
  _is_setup = false;
  _was_slot_over_sensor = false;
}


void ForceMeasurement::setup()
{
  _sensor.setup();
  
  _current_slot = _carousel->first_slot();
  _was_slot_over_sensor = false;
  _is_setup = true;
}


void ForceMeasurement::tick()
{
	if (!_is_setup)
	  return;
  
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
    
    int distance = (int)(_current_slot->odometer());
    
    if (distance >= _distance_at_last_measurement + 1)
    {
      if (_sensor.is_depressed())
      {
        _finish_with_slot(true);
        return;
      }
      _distance_at_last_measurement++;
    }
  }
  
}


//
// private
//


void ForceMeasurement::_finish_with_slot(boolean has_heavy_object)
{
  _current_slot->has_heavy_object = has_heavy_object;
  _current_slot = _carousel->next_slot(_current_slot);
  _was_slot_over_sensor = false;
}

boolean ForceMeasurement::_is_slot_over_sensor()
{
  return _current_slot->is_over(_start_angle, _end_angle);
}
