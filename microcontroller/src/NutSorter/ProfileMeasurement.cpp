#include "NutSorter.h"


namespace NutSorter
{
  
  //
  // public
  //
  
  
  void ProfileMeasurement::tick()
  {
    LightSensor* sensor = &Hardware::profile_light_sensor;
    
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
        _current_slot->profile.add_sample(distance, sensor->read());
        _distance_at_last_measurement++;
      }
    }
    
  }
  
  
  //
  // private
  //
  
  
  CoterminalAngle ProfileMeasurement::_start_angle = CoterminalAngle(295.0);
  CoterminalAngle ProfileMeasurement::_end_angle = CoterminalAngle(298.5);
  Slot* ProfileMeasurement::_current_slot = Carousel::first_slot();
  int ProfileMeasurement::_distance_at_last_measurement = 0;
  boolean ProfileMeasurement::_was_slot_over_sensor = false;
  
  
  void ProfileMeasurement::_finish_with_slot()
  {
    _current_slot = Carousel::next_slot(_current_slot);
    _was_slot_over_sensor = false;
  }
  
  
  boolean ProfileMeasurement::_is_slot_over_sensor()
  {
    return _current_slot->is_over(_start_angle);
  }
  
  
}
  
