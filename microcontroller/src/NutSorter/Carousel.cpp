#include "NutSorter.h"


namespace NutSorter
{
  
  //
  // public
  //
  
  
  CoterminalAngle Carousel::angle()
  {
    if (!_is_setup)
      return CoterminalAngle(0.0);
    
    return _motor()->angle();
  }
  
  
  Slot* Carousel::first_slot()
  {
    if (!_is_setup)
      return NULL;
    
    Slot* slot = &_slots[0];
    
    for (int slot_index = 0; slot_index < _slot_count(); slot_index++)
    {
      if (_slots[slot_index].start_angle().to_degrees() < slot->start_angle().to_degrees())
        slot = &_slots[slot_index];
    }
    return slot;
  }
  
  
  Slot* Carousel::next_slot(Slot* slot)
  {
    if (!_is_setup)
      return NULL;
    
    int slot_index = -1;
    int slot_count = _slot_count();
    for (int index = 0; index < slot_count; index++)
    {
      if (slot == &_slots[index])
      {
        slot_index = index;
        break;
      }
    }
    slot_index--;
    if (slot_index < 0)
      slot_index = slot_count - 1;
    return &_slots[slot_index];
  }
  
  
  void Carousel::setup()
  {
    LightSensor* light_sensor = &Hardware::carousel_calibrator_light_sensor;
    
    _motor()->turn(_direction, _speed);
    while (!light_sensor->is_lit())
      _motor()->tick();
    
    // if the system was started with the light sensor already
    // uncoverd we wont know the exact angle of the carusel
    // so now turn half a rotation and repeat to enusre an
    // accurate calibration proccess
    _motor()->turn_angle(CoterminalAngle(180.0), _direction, _speed);
    while (_motor()->is_turning())
      _motor()->tick();
    
    _motor()->turn(_direction, _speed);
    while (!light_sensor->is_lit())
      _motor()->tick();
    
    _motor()->turn_angle(_origin_offset, _direction, _speed);
    while (_motor()->is_turning())
      _motor()->tick();
    _motor()->reset_origin();
  }
  
  
  void Carousel::start()
  {
    _motor()->turn(_direction, _speed);
  }
  
  
  //
  // private
  //
  
  
  StepperMotor::Direction Carousel::_direction = StepperMotor::Direction::Forward;
  
  float Carousel::_speed = 4.0; // rpm
  
  CoterminalAngle Carousel::_origin_offset = CoterminalAngle(66.5); // this offset may need to be adjusted in different lighting condtions 
  
  Slot Carousel::_slots[] = { // here we add the slots 
    Slot(CoterminalAngle(33.5), CoterminalAngle(56.0)),
    Slot(CoterminalAngle(90.0), CoterminalAngle(113.0)),
    Slot(CoterminalAngle(150.5), CoterminalAngle(176.0)),
    Slot(CoterminalAngle(212.0), CoterminalAngle(236.0)),
    Slot(CoterminalAngle(274.0), CoterminalAngle(296.5)),
    Slot(CoterminalAngle(328.5), CoterminalAngle(356.0))
  };
  
  boolean Carousel::_is_setup = false;
  
  
  inline StepperMotor* Carousel::_motor()
  {
    return &Hardware::carousel_stepper_motor;
  }
  
  
  int Carousel::_slot_count()
  {
    return sizeof(_slots) / sizeof(_slots[0]);
  }
  
  
}
