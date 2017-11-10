#ifndef _NUT_SORTER_MAIN_H_
#define _NUT_SORTER_MAIN_H_

// parent for all the machine's functionality
// keeps the main file clean

#include <Arduino.h>
#include <Wire.h>

#include "NativeExtensions.h"
#include "CoterminalAngle.h"
#include "AdafruitMotorShield.h"
#include "Math.h"
#include "Timer.h"
#include "PeriodicTimer.h"
#include "HMC5883L.h"
#include "StepperMotor.h"


#include "Profile.h"
#include "Slot.h"
#include "LightSensor.h"
#include "Carousel.h"
#include "Chute.h"
#include "Interpreter.h"
#include "FerromagneticSensor.h"
#include "FerromagneticMeasurement.h"
#include "ConductivitySensor.h"
#include "ConductivityMeasurement.h"
#include "ForceSensor.h"
#include "ForceMeasurement.h"
#include "ProfileMeasurement.h"
#include "Initializer.h"


namespace NutSorter
{
  
  class Main
  {
    
    public:
    
    static AdafruitMotorShield motor_shield;
    static AdafruitStepperMotor* stepper_motor_driver;
    
    static StepperMotor stepper_motor;
    
    // here we declare all the system's concurrent tasks
  
    // all the angle offsets for every component can be adjusted here to
    //   account for any changes in hardware
    
    static Carousel carousel;
    static Chute chute;
    static Initializer initializer;
    static FerromagneticMeasurement ferromagnetic_measurement;
    static ConductivityMeasurement conductivity_measurement;
    static ForceMeasurement force_measurement;
    static ProfileMeasurement profile_measurement;
    static Interpreter interpreter;
    
    static void setup();
    static void start();
    static void tick();
    
  };
  
}

#endif
