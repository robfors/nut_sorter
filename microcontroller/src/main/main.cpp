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
#include "Disk.h"
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


AdafruitMotorShield AFMS = AdafruitMotorShield();
AdafruitStepperMotor* adafruit_stepper_motor = AFMS.getStepper(200, 2);
StepperMotor stepper_motor(adafruit_stepper_motor, 200, StepperMotor::StepType::Microstep, false);
Disk disk(&stepper_motor, Angle(66.5));
Chute chute;

Initializer initializer(&disk, Angle(360.0));
FerromagneticMeasurement ferromagnetic_measurement(&disk, Angle(123.0), Angle(125.5));
ConductivityMeasurement conductivity_measurement(&disk, Angle(179.0), Angle(196.5));
ForceMeasurement force_measurement(&disk, Angle(230.0), Angle(266.5));
ProfileMeasurement profile_measurement(&disk, Angle(295.0), Angle(298.5));
Interpreter interpreter(&disk, &chute, Angle(349.0));


void end()
{
  while (true) {}
}


void setup()
{
  Serial.begin(9600);
  Serial.println("|reset");
  Serial.println("calibrating...");
  Serial.println("|calibrating");
  AFMS.begin();
  disk.setup();
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
  disk.start();
}


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
