#ifndef _LIGHT_SENSOR_H_
#define _LIGHT_SENSOR_H_

/* This simple class reads a value from a specified analogue pin where
 * a light sensor is connected (after the amp curcit).
 * The pin is set HIGH, with high impedance.
 * When we read the pin, a higher voltage/value indicates more light.
 */

#include <Arduino.h>


class LightSensor
{
  
  public:
  
  LightSensor(int pin, unsigned int threshold);
  
  boolean is_lit();
  boolean is_unlit();
  int read();
  void setup();
  
  private:
  
  //const int _threshold = 500;
  
  boolean _is_setup;
  int _pin;
  unsigned int _threshold;
  
  boolean _is_lit();
  
};

#endif
