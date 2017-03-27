#ifndef _FERROMAGNETIC_SENSOR_H_
#define _FERROMAGNETIC_SENSOR_H_

#include <Arduino.h>
#include <Wire.h>
#include <HMC5883L.h>

#include "Timer.h"


// field is measured in milli-gauss

class FerromagneticSensor
{
  
  public:
  
  FerromagneticSensor();
  
  int field();
  boolean is_ferromagnetic_material_present();
  boolean setup();
  void tick();
  
  private:
  
  static const int _average_n_factor = 500; // samples
  static const int _sample_time = 1000; // ms
  static const int _threshold = 250; // milli-gauss
  
  float _average_a_factor;
  long _average_field;
  HMC5883L _compass;
  boolean _is_setup;
  Timer _sample_timer;
  
  boolean _is_ferromagnetic_material_present();
  
};

#endif
