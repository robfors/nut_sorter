#ifndef _INITIALIZER_H_
#define _INITIALIZER_H_

#include <Arduino.h>

#include "Slot.h"
#include "Disk.h"


class Initializer
{
  
  public:
  
  Initializer(Disk* disk, Angle start_angle);
  
  void setup();
  void tick();
  
  private:
  
  Slot* _next_slot;
  Disk* _disk;
  Angle _start_angle;
  boolean _is_setup;
  
  void _process_slot(Slot* slot);
  
};

#endif
