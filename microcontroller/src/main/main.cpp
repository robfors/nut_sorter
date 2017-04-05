#include <Arduino.h>
#include <Wire.h>

#include "Angle.h"
#include "AdafruitMotorShield.h"
#include "Math.h"
#include "Timer.h"
#include "PeriodicTimer.h"
#include "Profile.h"
#include "Slot.h"
#include "LightSensor.h"
#include "StepperMotor.h"
#include "Carousel.h"
#include "VarSpeedServo.h"
#include "Servo.h"
#include "Chute.h"
#include "Interpreter.h"
#include "HMC5883L.h"
#include "FerromagneticSensor.h"
#include "FerromagneticMeasurement.h"
#include "ConductivitySensor.h"
#include "ConductivityMeasurement.h"
#include "ForceSensor.h"
#include "ForceMeasurement.h"
#include "ProfileMeasurement.h"
#include "Initializer.h"

// here we declare all the system's concurrent tasks

// all the angle offsets for every component can be adjusted here to
//   account for any changes in hardware
AdafruitMotorShield AFMS = AdafruitMotorShield();
AdafruitStepperMotor* adafruit_stepper_motor = AFMS.getStepper(200, 2);
StepperMotor stepper_motor(adafruit_stepper_motor, 200, StepperMotor::StepType::Microstep, false);
Carousel carousel(&stepper_motor, Angle(66.5)); // this offset may need to be adjusted in different lighting condtions 
Chute chute;

Initializer initializer(&carousel, Angle(360.0));
FerromagneticMeasurement ferromagnetic_measurement(&carousel, Angle(123.0), Angle(125.5));
ConductivityMeasurement conductivity_measurement(&carousel, Angle(179.0), Angle(196.5));
ForceMeasurement force_measurement(&carousel, Angle(230.0), Angle(266.5));
ProfileMeasurement profile_measurement(&carousel, Angle(295.0), Angle(298.5));
Interpreter interpreter(&carousel, &chute, Angle(349.0));

// call this in the event of an error
void end()
{
  while (true) {}
}

// setup every task (eg. pin modes)
// some return false to indicate an error
void setup()
{
  Serial.begin(9600);
  Serial.println("|reset");
  Serial.println("calibrating...");
  Serial.println("|calibrating");
  AFMS.begin();
  carousel.setup();
  chute.setup();
  initializer.setup();
  if (!ferromagnetic_measurement.setup())
  {
    Serial.println("ferromagnetic measurer setup error...");
    Serial.println("|setup_error");
    end();
  }
  if (!conductivity_measurement.setup())
  {
    Serial.println("conductivity measurer setup error...");
    Serial.println("|setup_error");
    end();
  }
  force_measurement.setup();
  profile_measurement.setup();
  interpreter.setup();
  delay(5000);
  Serial.println("ready...");
  Serial.println("|running");
  carousel.start();
}

// this is the reactor loop
// no calls should block here!
// if they do, all other tasks will miss deadlines
// the tick() method is called for each task
//    often the task will simply return
//    sometimes the task will have work do to, it will quickly run and return
//    execution to the ractor loop for the next task
void loop()
{
  stepper_motor.tick();
  initializer.tick();
  ferromagnetic_measurement.tick();
  conductivity_measurement.tick();
  force_measurement.tick();
  profile_measurement.tick();
  interpreter.tick();
}
