#include "Interpreter.h"


//
// public
//


Interpreter::Interpreter(Disk* disk, Angle start_angle)
{
  _disk = disk;
  _next_slot = NULL;
  _start_angle = start_angle;
  _is_setup = false;
}


void Interpreter::setup()
{
  _next_slot = _disk->first_slot();  
  _is_setup = true;
}


void Interpreter::tick()
{
	if (!_is_setup)
	  return;
  
  if (_next_slot->is_over(_start_angle))
  {
    _process_slot(_next_slot);
    _next_slot = _disk->next_slot(_next_slot);
  }
}


//
// private
//


void Interpreter::_process_slot(Slot* slot)
{
  Serial.println("slot: ");
  Serial.print("object ferromagnetic? ");
  Serial.println(slot->has_ferromagnetic_object);
  Serial.print("object conductive? ");
  Serial.println(slot->has_conductive_object);
  Serial.print("object heavy? ");
  Serial.println(slot->has_heavy_object);
}
