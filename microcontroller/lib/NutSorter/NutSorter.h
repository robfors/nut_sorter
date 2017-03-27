#ifndef _NUT_SORTER_H_
#define _NUT_SORTER_H_

#include <Arduino.h>
#include <Wire.h>

#include "Angle.h"
#include "AdafruitMotorShield.h"
#include "Math.h"
#include "Timer.h"
#include "PeriodicTimer.h"
#include "Slot.h"
#include "LightSensor.h"
#include "StepperMotor.h"
#include "Disk.h"
#include "Interpreter.h"
#include "HMC5883L.h"
#include "FerromagneticSensor.h"
#include "FerromagneticMeasurement.h"
#include "ConductivitySensor.h"
#include "ConductivityMeasurement.h"
#include "ForceSensor.h"
#include "ForceMeasurement.h"
#include "Initializer.h"


class NutSorter
{
  
  public:
  
  NutSorter();
  
  void turn_to();
  
  private:
  
  Slot* _next_slot;
  Disk* _disk;
  Angle _start_angle;
  boolean _is_setup;
  
  void _process_slot(Slot* slot);
  
};

#endif
