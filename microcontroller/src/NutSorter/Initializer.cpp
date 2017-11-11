#include "NutSorter.h"


namespace NutSorter
{
  
  //
  // public
  //
  
  
  void Initializer::tick()
  {
    if (_next_slot->is_over(_start_angle))
    {
      _process_slot(_next_slot);
      _next_slot = Carousel::next_slot(_next_slot);
    }
  }
  
  
  //
  // private
  //
  
  
  Slot* Initializer::_next_slot = Carousel::first_slot();
  CoterminalAngle Initializer::_start_angle = CoterminalAngle(360.0);
  
  
  void Initializer::_process_slot(Slot* slot)
  {
    slot->has_ferromagnetic_object = false;
    slot->has_conductive_object = false;
    slot->has_heavy_object = false;
    slot->profile.clear();
  }
  
}
