#include "Angle.h"


//
// public
//


Angle Angle::from_degrees(float degrees)
{
  return Angle(degrees);
}


Angle Angle::from_revolution(float revolution)
{
  return Angle(revolution * 360.0);
}


Angle::Angle()
{
  _angle = 0.0;
}


Angle::Angle(float angle)
{
  _angle = _clean(angle);
}


boolean Angle::is_between(Angle start_angle, Angle end_angle)
{
  float start_angle_float = start_angle.to_degrees();
  float end_angle_float = end_angle.to_degrees();
  float angle_float = to_degrees();
  
  //fix jump of angle
  if (end_angle_float < start_angle_float )
  {
    end_angle_float += 360.0;
    if (angle_float < start_angle_float)
      angle_float += 360.0;
  }
  
  return start_angle_float <= angle_float && end_angle_float >= angle_float;
}


Angle Angle::operator+(Angle other_angle)
{
    float new_angle = _clean(_angle + other_angle.to_degrees());
    return Angle(new_angle);
}


Angle Angle::operator-(Angle other_angle)
{
    float new_angle = _clean(_angle - other_angle.to_degrees());
    return Angle(new_angle);
}


Angle Angle::operator=(Angle* other_angle)
{
    return Angle(other_angle->to_degrees());
}


boolean Angle::operator==(Angle other_angle)
{
  return _angle == other_angle.to_degrees();
}


float Angle::to_degrees()
{
  return _angle;
}


float Angle::to_revolution()
{
  return _angle / 360.0;
}


//
// private
//


float Angle::_clean(float angle)
{
  while (angle > 360.0)
    angle -= 360.0;
  while (angle < 0)
    angle += 360.0;
  return angle;
}
