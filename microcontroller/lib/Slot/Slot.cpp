#include "Slot.h"

#include "Carousel.h"

//
// public
//


Slot::Slot(Carousel* carousel, Angle start_offset_angle, Angle end_offset_angle)
{
  has_ferromagnetic_object = false;
  has_conductive_object = false;
  has_heavy_object = false;
  profile.clear();
  
  _carousel = carousel;
  _end_offset_angle = end_offset_angle;
  _odometer_start_angle = 0.0;
  _start_offset_angle = start_offset_angle;
}


boolean Slot::is_over(Angle angle)
{
  return angle.is_between(start_angle(), end_angle());
}


boolean Slot::is_over(Angle sensor_start_angle, Angle sensor_end_angle)
{
  return 
    sensor_start_angle.is_between(start_angle(), end_angle()) ||
    sensor_end_angle.is_between(start_angle(), end_angle()) ||
    start_angle().is_between(sensor_start_angle, sensor_end_angle) ||
    end_angle().is_between(sensor_start_angle, sensor_end_angle);
}


int Slot::odometer()
{
  Angle angle_moved = start_angle() - _odometer_start_angle;
  float revolution_moved = angle_moved.to_revolution();
  return _revolution_circumference * revolution_moved;
}


void Slot::reset_odometer()
{
  _odometer_start_angle = start_angle();
}


Angle Slot::start_angle()
{
  return _carousel->angle() + _start_offset_angle;
}


Angle Slot::end_angle()
{
  return _carousel->angle() + _end_offset_angle;
}


boolean Slot::operator==(const Slot* other_slot)
{
  return
    _start_offset_angle == other_slot->_start_offset_angle &&
    _end_offset_angle == other_slot->_end_offset_angle;
}


//
// private
//
