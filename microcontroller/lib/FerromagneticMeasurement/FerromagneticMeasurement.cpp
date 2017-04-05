#include "FerromagneticMeasurement.h"


//
// public
//


FerromagneticMeasurement::FerromagneticMeasurement(Carousel* carousel, Angle start_angle, Angle end_angle)
{
  _end_angle = end_angle;
  _carousel = carousel;
  _current_slot = NULL;
  _distance_at_last_measurement = 0;
  _start_angle = start_angle;
  _is_setup = false;
  _was_slot_over_sensor = false;
}


boolean FerromagneticMeasurement::setup()
{
  if (!_sensor.setup())
    return false;
  _current_slot = _carousel->first_slot();
  _was_slot_over_sensor = false;

  _is_setup = true;
  return true;
}


void FerromagneticMeasurement::tick()
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
    
    int distance = (int)(_current_slot->odometer());
    
    if (distance >= _distance_at_last_measurement + 1)
    {
      //Serial.println(_sensor.field());
      if (_sensor.is_ferromagnetic_material_present())
      {
        _finish_with_slot(true);
        return;
      }
      else
        _distance_at_last_measurement++;
    }
  }
}


//
// private
//


void FerromagneticMeasurement::_finish_with_slot(boolean has_ferromagnetic_object)
{
  _current_slot->has_ferromagnetic_object = has_ferromagnetic_object;
  _current_slot = _carousel->next_slot(_current_slot);
  _was_slot_over_sensor = false;
}

boolean FerromagneticMeasurement::_is_slot_over_sensor()
{
  return _current_slot->is_over(_start_angle, _end_angle);
}
