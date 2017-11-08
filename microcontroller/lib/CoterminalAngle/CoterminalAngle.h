#ifndef _COTERMINAL_ANGLE_H_
#define _COTERMINAL_ANGLE_H_

/* It should be noted that in the context of the this project,
 * coterminal angles can only range from 0 to 360 degrees, that is an
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


class CoterminalAngle
{
  
  public:
  
  static CoterminalAngle from_degrees(float degrees);
  static CoterminalAngle from_revolution(float revolution);
  static CoterminalAngle zero();
  
  CoterminalAngle();
  CoterminalAngle(float angle);
  
  boolean is_between(const CoterminalAngle start_angle, const CoterminalAngle end_angle);
  CoterminalAngle operator+(CoterminalAngle other_angle);
  CoterminalAngle operator-(CoterminalAngle other_angle);
  CoterminalAngle operator=(CoterminalAngle* other_angle);
  boolean operator==(CoterminalAngle other_angle);
  float to_degrees();
  float to_revolution();
  
  
  private:
  
  float _angle;
  
  // ensure angle is only between 0 and 360 degress
  float _clean(float angle);
  
};

#endif
