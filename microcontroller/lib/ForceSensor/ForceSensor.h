#ifndef _FORCE_SENSOR_H_
#define _FORCE_SENSOR_H_

#include <Arduino.h>


class ForceSensor
{
  
  public:
  
  ForceSensor(int pin);
  
  boolean is_depressed();
  void setup();
  
  private:
  
  static const int _threshold = 500;
  
  boolean _is_setup;
  int _pin;
  
  boolean _is_depressed();
  
};

#endif