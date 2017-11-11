#include "NutSorter.h"


namespace NutSorter
{
  
  //
  // public
  //
  
  
  void ForceMeasurement::tick()
  {
    Hardware::ForceSensor* sensor = &Hardware::Main::force_sensor;
    
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
        if (sensor->is_depressed())
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
  
  
  CoterminalAngle ForceMeasurement::_start_angle = CoterminalAngle(230.0);
  CoterminalAngle ForceMeasurement::_end_angle = CoterminalAngle(266.5);
  Slot* ForceMeasurement::_current_slot = Carousel::first_slot();
  int ForceMeasurement::_distance_at_last_measurement = 0;
  boolean ForceMeasurement::_was_slot_over_sensor = false;
  
  
  void ForceMeasurement::_finish_with_slot(boolean has_heavy_object)
  {
    _current_slot->has_heavy_object = has_heavy_object;
    _current_slot = Carousel::next_slot(_current_slot);
    _was_slot_over_sensor = false;
  }
  
  
  boolean ForceMeasurement::_is_slot_over_sensor()
  {
    return _current_slot->is_over(_start_angle, _end_angle);
  }
  
  
}
  
