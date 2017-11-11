#include "NutSorter.h"


//
// public
//


NutSorter::LightSensor::LightSensor(int pin, unsigned int threshold)
{
  _pin = pin;
  _is_setup = false;
  _threshold = threshold;
}


boolean NutSorter::LightSensor::is_lit()
{
  if (!_is_setup)
    return false;
  
  return _is_lit();
}


boolean NutSorter::LightSensor::is_unlit()
{
  return !is_lit();
}


int NutSorter::LightSensor::read()
{
  return analogRead(_pin);
}

void NutSorter::LightSensor::setup()
{
  pinMode(_pin, INPUT_PULLUP);
  _is_setup = true;
}


//
// private
//


boolean NutSorter::LightSensor::_is_lit()
{
	//Serial.println(analogRead(_pin));
  return analogRead(_pin) < _threshold;
}
