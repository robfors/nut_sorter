#include "NutSorter.h"


namespace NutSorter
{
  
  //
  // public
  //
  
  
  void FerromagneticMeasurement::tick()
  {
    Hardware::FerromagneticSensor* sensor = &Hardware::Main::ferromagnetic_sensor;
    
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
        if (sensor->is_ferromagnetic_material_present())
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
  
  
  Slot* FerromagneticMeasurement::_current_slot = Carousel::first_slot();
  boolean FerromagneticMeasurement::_was_slot_over_sensor = false;
  CoterminalAngle FerromagneticMeasurement::_start_angle = CoterminalAngle(123.0);
  CoterminalAngle FerromagneticMeasurement::_end_angle = CoterminalAngle(125.5);
  int FerromagneticMeasurement::_distance_at_last_measurement = 0;
    
  
  void FerromagneticMeasurement::_finish_with_slot(boolean has_ferromagnetic_object)
  {
    _current_slot->has_ferromagnetic_object = has_ferromagnetic_object;
    _current_slot = Carousel::next_slot(_current_slot);
    _was_slot_over_sensor = false;
  }
  
  
  boolean FerromagneticMeasurement::_is_slot_over_sensor()
  {
    return _current_slot->is_over(_start_angle, _end_angle);
  }
  
}
