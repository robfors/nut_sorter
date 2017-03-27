#ifndef _ANGLE_H_
#define _ANGLE_H_

#include <Arduino.h>


class Angle
{
  
  public:
  
  static Angle from_degrees(float degrees);
  static Angle from_revolution(float revolution);
  
  Angle();
  Angle(float angle);
  
  boolean is_between(const Angle angle_1, const Angle angle_2);
  Angle operator+(Angle other_angle);
  Angle operator-(Angle other_angle);
  Angle operator=(Angle* other_angle);
  boolean operator==(Angle other_angle);
  float to_degrees();
  float to_revolution();
  
  
  private:
  
  float _angle;
  
  float _clean(float angle);
  
};

#endif
