#include "Carousel.h"


const float Carousel::_speed = 4.0; // rpm


//
// public
//


Carousel::Carousel(StepperMotor* motor, Angle origin_offset)
: _light_sensor(_light_sensor_pin, _light_sensor_threshold),
  _slots{
    // here we add the slots
    Slot(this, Angle(33.5), Angle(56.0)),
    Slot(this, Angle(90.0), Angle(113.0)),
    Slot(this, Angle(150.5), Angle(176.0)),
    Slot(this, Angle(212.0), Angle(236.0)),
    Slot(this, Angle(274.0), Angle(296.5)),
    Slot(this, Angle(328.5), Angle(356.0))
  }
{
  _is_setup = false;
  _motor = motor;
  _origin_offset = origin_offset;
}


Angle Carousel::angle()
{
  if (!_is_setup)
    return Angle(0.0);
  
  return _motor->angle();
}


Slot* Carousel::first_slot()
{
  if (!_is_setup)
    return NULL;
  
  Slot* slot = &_slots[0];
  
  for (int slot_index = 0; slot_index < _num_slots; slot_index++)
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
  //int num_slots = sizeof(_slots)/sizeof(_slots[0]);
  for (int index = 0; index < _num_slots; index++)
  {
    if (slot == &_slots[index])
    {
      slot_index = index;
      break;
    }
  }
  slot_index--;
  if (slot_index < 0)
    slot_index = _num_slots - 1;
  return &_slots[slot_index];
}


void Carousel::setup()
{
  _light_sensor.setup();
  
  _motor->turn(_direction, _speed);
  while (!_light_sensor.is_lit())
    _motor->tick();
  
  // if the system was started with the light sensor already
  // uncoverd we wont know the exact angle of the carusel
  // so now turn half a rotation and repeat to enusre an
  // accurate calibration proccess
  _motor->turn_angle(Angle(180.0), _direction, _speed);
  while (_motor->is_turning())
    _motor->tick();
  
  _motor->turn(_direction, _speed);
  while (!_light_sensor.is_lit())
    _motor->tick();
  
  _motor->turn_angle(_origin_offset, _direction, _speed);
  while (_motor->is_turning())
    _motor->tick();
  _motor->reset_origin();
  
  _is_setup = true;
}


void Carousel::start()
{
  if (!_is_setup)
    return;
  
  _motor->turn(_direction, _speed);
}


//
// private
//
