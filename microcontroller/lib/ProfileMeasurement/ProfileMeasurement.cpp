#include "ProfileMeasurement.h"


//
// public
//


ProfileMeasurement::ProfileMeasurement(Carousel* carousel, Angle start_angle, Angle end_angle)
: _sensor(_pin, _light_sensor_threshold)
{
  _end_angle = end_angle;
  _carousel = carousel;
  _current_slot = NULL;
  _distance_at_last_measurement = 0;
  _start_angle = start_angle;
  _is_setup = false;
  _was_slot_over_sensor = false;
}


void ProfileMeasurement::setup()
{
  _sensor.setup();
  
  _current_slot = _carousel->first_slot();
  _was_slot_over_sensor = false;
  _is_setup = true;
}


void ProfileMeasurement::tick()
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
      _finish_with_slot();
      return;
    }
    
    int distance = (int)(_current_slot->odometer());
    
    if (distance >= _distance_at_last_measurement + 1)
    {
      
      //Serial.println(_sensor.read());
      //Serial.println((byte)_sensor.read());
      _current_slot->profile.add_sample(distance, _sensor.read());
      _distance_at_last_measurement++;
    }
  }
  
}


//
// private
//


void ProfileMeasurement::_finish_with_slot()
{
  _current_slot = _carousel->next_slot(_current_slot);
  _was_slot_over_sensor = false;
}

boolean ProfileMeasurement::_is_slot_over_sensor()
{
  //return _current_slot->is_over(_start_angle, _end_angle);
  return _current_slot->is_over(_start_angle);
}
