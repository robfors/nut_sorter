#ifndef _NUT_SORTER_NUT_SORTER_H_
#define _NUT_SORTER_NUT_SORTER_H_

// parent for all the machine's functionality
// keeps the main file clean

#include <Arduino.h>
#include <Wire.h>

#include "CoterminalAngle.h"
#include "AdafruitMotorShield.h"
#include "Math.h"
#include "Timer.h"
#include "PeriodicTimer.h"
#include "Slot.h"
#include "LightSensor.h"
#include "StepperMotor.h"
#include "Carousel.h"
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
  

  
  private:
  

  
};

#endif
