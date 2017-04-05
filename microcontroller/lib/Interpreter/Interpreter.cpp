#include "Interpreter.h"


//
// public
//


Interpreter::Interpreter(Carousel* carousel, Chute* chute, Angle start_angle)
{
  _chute = chute;
  _carousel = carousel;
  _next_slot = NULL;
  _start_angle = start_angle;
  _is_setup = false;
}


void Interpreter::setup()
{
  _next_slot = _carousel->first_slot();  
  _is_setup = true;
}


void Interpreter::tick()
{
	if (!_is_setup)
	  return;
  
  if (_next_slot->is_over(_start_angle))
  {
    _process_slot(_next_slot);
    _next_slot = _carousel->next_slot(_next_slot);
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
  Serial.print("average object profile sample: ");
  Serial.println(slot->profile.average_sample());
  
  Chute::ObjectType object_type;
  
  if (slot->profile.average_sample() > 295)
    object_type = Chute::ObjectType::Coin;
  else if (slot->has_ferromagnetic_object)
    object_type = Chute::ObjectType::SmallSteelNut;
  else if (slot->has_heavy_object)
    object_type = Chute::ObjectType::BigBrassNut;
  else if (slot->has_conductive_object)
    object_type = Chute::ObjectType::SmallBrassNut;
  else if (slot->profile.average_sample() > 110)
    object_type = Chute::ObjectType::BigNylonNut;
  else
    object_type = Chute::ObjectType::Empty;
  
  // this print out is for the gui to keep counts
  switch (object_type)
  {
  case Chute::ObjectType::SmallSteelNut:
    Serial.println("|small_steel_nut");
    break;
  case Chute::ObjectType::BigBrassNut:
    Serial.println("|big_brass_nut");
    break;
  case Chute::ObjectType::BigNylonNut:
    Serial.println("|big_nylon_nut");
    break;
  case Chute::ObjectType::SmallBrassNut:
    Serial.println("|small_brass_nut");
    break;
  case Chute::ObjectType::Coin:
    Serial.println("|coin");
    break;
  }
  
  _chute->turn_to_cup_for(object_type);
}
