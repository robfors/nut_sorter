#ifndef _ANGLE_H_
#define _ANGLE_H_

/* It should be noted that in the context of the this project,
 * angles can only range from 0 to 360 degrees, that is an
 * angle of 10 degrees is equivalent to 370 degrees and -350 degress.
 * 
 * The main purpose this class exists is to allow other code to easily
 * work with and compare angles, with out requiring the classes to
 * implement all the comparison logic.
 * 
 * This class also offers the conversion between degrees and
 * revolutions (a revolution being 360 degrees)
 */


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
  
  // ensure angle is only between 0 and 360 degress
  float _clean(float angle);
  
};

#endif
