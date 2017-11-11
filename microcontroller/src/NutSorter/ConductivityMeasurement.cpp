#include "NutSorter.h"


namespace NutSorter
{
  
    
  //
  // public
  //
  
  
  void ConductivityMeasurement::tick()
  {
    ConductivitySensor* sensor = &Hardware::conductivity_sensor;
    
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
      
      if (sensor->is_result_ready())
      {
        if (sensor->result())
        {
          _finish_with_slot(true);
          return;
        }
      }
      
      int distance = (int)(_current_slot->odometer());
      
      if (distance >= _distance_at_last_measurement + 1)
      {
        sensor->measure();
        _distance_at_last_measurement++;
      }
    }
    
  }
  
  
  //
  // private
  //
  
  
  CoterminalAngle ConductivityMeasurement::_start_angle = CoterminalAngle(179.0);
  
  CoterminalAngle ConductivityMeasurement::_end_angle = CoterminalAngle(196.5);
  
  int ConductivityMeasurement::_distance_at_last_measurement = 0;
  
  boolean ConductivityMeasurement::_was_slot_over_sensor = false;
  
  Slot* ConductivityMeasurement::_current_slot = Carousel::first_slot();
  
  
  void ConductivityMeasurement::_finish_with_slot(boolean has_conductive_object)
  {
    _current_slot->has_conductive_object = has_conductive_object;
    _current_slot = Carousel::next_slot(_current_slot);
    _was_slot_over_sensor = false;
  }
  
  
  boolean ConductivityMeasurement::_is_slot_over_sensor()
  {
    return _current_slot->is_over(_start_angle, _end_angle);
  }
  
  
}
