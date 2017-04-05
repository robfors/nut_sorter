#ifndef _FERROMAGNETIC_SENSOR_H_
#define _FERROMAGNETIC_SENSOR_H_

/* This code communicates with a HMC5883L magnetometer to test for a
 * ferromagnetic material. Given this was not the intended use the HMC5883L
 * some functionality had to be added to this class.
 * The HMC5883L's values are different every time it starts.
 * To solve for this we obtain an average value that the sensor naturaly
 * seems to be operating at. This average is continuously updaded with
 * a moving average on every tick().
 * when we call 'is_ferromagnetic_material_present()', it will compare the
 * current value begin returned from the HMC5883L with the average and we
 * can assume a ferromagnetic object is present if the differnce is
 * greater then the threshold specified in this header.
 * 
 */

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
