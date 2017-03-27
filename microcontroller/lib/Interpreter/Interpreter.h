#ifndef _INTERPRETER_H_
#define _INTERPRETER_H_

#include <Arduino.h>

#include "Slot.h"
#include "Disk.h"
#include "Chute.h"
#include "Profile.h"


class Interpreter
{
  
  public:
  
  Interpreter(Disk* disk, Chute* chute, Angle start_angle);
  
  void setup();
  void tick();
  
  private:
  
  Chute* _chute;
  Slot* _next_slot;
  Disk* _disk;
  Angle _start_angle;
  boolean _is_setup;
  
  void _process_slot(Slot* slot);
  
};

#endif
