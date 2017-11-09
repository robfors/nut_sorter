#include "Slot.h"
#include "Carousel.h"


//
// public
//


NutSorter::Slot::Slot(Carousel* carousel, CoterminalAngle start_offset_angle, CoterminalAngle end_offset_angle)
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


boolean NutSorter::Slot::is_over(CoterminalAngle angle)
{
  return angle.is_between(start_angle(), end_angle());
}


boolean NutSorter::Slot::is_over(CoterminalAngle sensor_start_angle, CoterminalAngle sensor_end_angle)
{
  return 
    sensor_start_angle.is_between(start_angle(), end_angle()) ||
    sensor_end_angle.is_between(start_angle(), end_angle()) ||
    start_angle().is_between(sensor_start_angle, sensor_end_angle) ||
    end_angle().is_between(sensor_start_angle, sensor_end_angle);
}


int NutSorter::Slot::odometer()
{
  CoterminalAngle angle_moved = start_angle() - _odometer_start_angle;
  float revolution_moved = angle_moved.to_revolution();
  return _revolution_circumference * revolution_moved;
}


void NutSorter::Slot::reset_odometer()
{
  _odometer_start_angle = start_angle();
}


CoterminalAngle NutSorter::Slot::start_angle()
{
  return _carousel->angle() + _start_offset_angle;
}


CoterminalAngle NutSorter::Slot::end_angle()
{
  return _carousel->angle() + _end_offset_angle;
}


boolean NutSorter::Slot::operator==(const Slot* other_slot)
{
  return
    _start_offset_angle == other_slot->_start_offset_angle &&
    _end_offset_angle == other_slot->_end_offset_angle;
}


//
// private
//
