#include "NutSorter.h"


//
// public
//


NutSorter::ForceSensor::ForceSensor(int pin)
{
  _pin = pin;
  _is_setup = false;
}


boolean NutSorter::ForceSensor::is_depressed()
{
  if (!_is_setup)
    return false;

  return _is_depressed();
}


void NutSorter::ForceSensor::setup()
{
  pinMode(_pin, INPUT);
  _is_setup = true;
  return true;
}


//
// private
//


boolean NutSorter::ForceSensor::_is_depressed()
{
  //Serial.println(analogRead(_pin));
  return analogRead(_pin) > _threshold;
}
