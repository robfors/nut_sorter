#include "CoterminalAngle.h"


//
// public
//


CoterminalAngle CoterminalAngle::from_degrees(float degrees)
{
  return CoterminalAngle(degrees);
}


CoterminalAngle CoterminalAngle::from_revolution(float revolution)
{
  return CoterminalAngle(revolution * 360.0);
}


CoterminalAngle CoterminalAngle::zero()
{
  return CoterminalAngle();
}


CoterminalAngle::CoterminalAngle()
{
  _angle = 0.0;
}


CoterminalAngle::CoterminalAngle(float angle)
{
  _angle = _clean(angle);
}


boolean CoterminalAngle::is_between(CoterminalAngle start_angle, CoterminalAngle end_angle)
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


CoterminalAngle CoterminalAngle::operator+(CoterminalAngle other_angle)
{
    float new_angle = _clean(_angle + other_angle.to_degrees());
    return CoterminalAngle(new_angle);
}


CoterminalAngle CoterminalAngle::operator-(CoterminalAngle other_angle)
{
    float new_angle = _clean(_angle - other_angle.to_degrees());
    return CoterminalAngle(new_angle);
}


CoterminalAngle CoterminalAngle::operator=(CoterminalAngle* other_angle)
{
    return CoterminalAngle(other_angle->to_degrees());
}


boolean CoterminalAngle::operator==(CoterminalAngle other_angle)
{
  return _angle == other_angle.to_degrees();
}


float CoterminalAngle::to_degrees()
{
  return _angle;
}


float CoterminalAngle::to_revolution()
{
  return _angle / 360.0;
}


//
// private
//


float CoterminalAngle::_clean(float angle)
{
  while (angle > 360.0)
    angle -= 360.0;
  while (angle < 0)
    angle += 360.0;
  return angle;
}
