#ifndef _SLOT_H_
#define _SLOT_H_

/* We use these objects to give the code base access to each slots start
 * and end angle at any point in time.
 * 
 * It also acts as a storage for measurment data.
 */

#include <Arduino.h>

#include "Math.h"
#include "Angle.h"
#include "Profile.h"


class Carousel;

class Slot
{
  
  public:
  
  boolean has_ferromagnetic_object;
  boolean has_conductive_object;
  boolean has_heavy_object;
  Profile profile;
  
  Slot(Carousel* carousel, Angle start_offset_angle, Angle end_offset_angle);
  
  boolean is_over(Angle angle);
  boolean is_over(Angle start_angle, Angle end_angle);
  int odometer();
  void reset_odometer();
  Angle start_angle();
  Angle end_angle();
  
  boolean operator==(const Slot* other_slot);
  
  private:
  
  static const int _revolution_radius = 85; // mm
  static const int _revolution_circumference = _revolution_radius * M_PI; // mm
  
  Carousel* _carousel;
  Angle _end_offset_angle;
  Angle _odometer_start_angle;
  Angle _start_offset_angle;
  
};

#endif
