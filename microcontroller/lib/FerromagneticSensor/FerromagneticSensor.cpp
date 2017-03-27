#include "FerromagneticSensor.h"


//
// public
//


FerromagneticSensor::FerromagneticSensor()
: _sample_timer(_sample_time, Timer::Units::Milliseconds)
{
  _average_a_factor = (float)2/(_average_n_factor+1);
  _compass = HMC5883L();
  _is_setup = false;
}


int FerromagneticSensor::field()
{
	return (int)_compass.readNormalize().ZAxis;
}


boolean FerromagneticSensor::is_ferromagnetic_material_present()
{
  if (!_is_setup)
    return false;
  
  return _is_ferromagnetic_material_present();
}


boolean FerromagneticSensor::setup()
{
  if (!_compass.begin())
    return false;
  
  // Set measurement range
  // +/- 0.88 Ga: HMC5883L_RANGE_0_88GA
  // +/- 1.30 Ga: HMC5883L_RANGE_1_3GA (default)
  // +/- 1.90 Ga: HMC5883L_RANGE_1_9GA
  // +/- 2.50 Ga: HMC5883L_RANGE_2_5GA
  // +/- 4.00 Ga: HMC5883L_RANGE_4GA
  // +/- 4.70 Ga: HMC5883L_RANGE_4_7GA
  // +/- 5.60 Ga: HMC5883L_RANGE_5_6GA
  // +/- 8.10 Ga: HMC5883L_RANGE_8_1GA
  _compass.setRange(HMC5883L_RANGE_1_3GA);
  
  // Set measurement mode
  // Idle mode:              HMC5883L_IDLE
  // Single-Measurement:     HMC5883L_SINGLE
  // Continuous-Measurement: HMC5883L_CONTINOUS (default)
  _compass.setMeasurementMode(HMC5883L_CONTINOUS);
  
  // Set data rate
  //  0.75Hz: HMC5883L_DATARATE_0_75HZ
  //  1.50Hz: HMC5883L_DATARATE_1_5HZ
  //  3.00Hz: HMC5883L_DATARATE_3HZ
  //  7.50Hz: HMC5883L_DATARATE_7_50HZ
  // 15.00Hz: HMC5883L_DATARATE_15HZ (default)
  // 30.00Hz: HMC5883L_DATARATE_30HZ
  // 75.00Hz: HMC5883L_DATARATE_75HZ
  _compass.setDataRate(HMC5883L_DATARATE_15HZ);
  
  // Set number of samples averaged
  // 1 sample:  HMC5883L_SAMPLES_1 (default)
  // 2 samples: HMC5883L_SAMPLES_2
  // 4 samples: HMC5883L_SAMPLES_4
  // 8 samples: HMC5883L_SAMPLES_8
  _compass.setSamples(HMC5883L_SAMPLES_1);
  
  
  
  //calibrate average_field
  _average_field = 0;
  int sample_times = 50;
  for (int i = 0; i < sample_times; i++)
  {
    _average_field += field();
    delay(100);
  }
  _average_field = _average_field / sample_times;
  
  _sample_timer.start();
  
  //unsigned int time_to_wait = 10000;
  //Timer timer(time_to_wait, Timer::Units::Milliseconds);
  //timer.start();
  //while (timer.is_running())
  //  tick();
  
  _is_setup = true;
  return true;
}


void FerromagneticSensor::tick()
{
	if (!_is_setup)
	  return;
  
  if (_sample_timer.is_complete())
  {
  	_average_field = _average_a_factor*field() + (1-_average_a_factor)*_average_field;
    _sample_timer.start();
	}
}


//
// private
//


boolean FerromagneticSensor::_is_ferromagnetic_material_present()
{
	int current_field = field();
  //Serial.println(current_field);
	return current_field > _average_field + _threshold || current_field < _average_field - _threshold;
}
