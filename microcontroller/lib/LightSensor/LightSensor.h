#ifndef _LIGHT_SENSOR_H_
#define _LIGHT_SENSOR_H_

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
