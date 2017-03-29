#include "Initializer.h"


//
// public
//


Initializer::Initializer(Disk* disk, Angle start_angle)
{
  _disk = disk;
  _next_slot = NULL;
  _start_angle = start_angle;
  _is_setup = false;
}


void Initializer::setup()
{
  _next_slot = _disk->first_slot();  
  _is_setup = true;
}


void Initializer::tick()
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


void Initializer::_process_slot(Slot* slot)
{
  slot->has_ferromagnetic_object = false;
  slot->has_conductive_object = false;
  slot->has_heavy_object = false;
  slot->profile.clear();
}