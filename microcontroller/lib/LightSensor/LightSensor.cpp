#include "LightSensor.h"


//
// public
//


LightSensor::LightSensor(int pin, unsigned int threshold)
{
  _pin = pin;
  _is_setup = false;
  _threshold = threshold;
}


boolean LightSensor::is_lit()
{
  if (!_is_setup)
    return false;
  
  return _is_lit();
}


boolean LightSensor::is_unlit()
{
  return !is_lit();
}


int LightSensor::read()
{
  return analogRead(_pin);
}

void LightSensor::setup()
{
  pinMode(_pin, INPUT_PULLUP);
  _is_setup = true;
}


//
// private
//


boolean LightSensor::_is_lit()
{
	//Serial.println(analogRead(_pin));
  return analogRead(_pin) < _threshold;
}
