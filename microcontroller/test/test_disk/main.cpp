#include <Arduino.h>
#include <Wire.h>

#include "AdafruitMotorShield.h"
#include "Math.h"
#include "Timer.h"
#include "PeriodicTimer.h"
#include "Slot.h"
#include "LightSensor.h"
#include "StepperMotor.h"
#include "Carousel.h"


AdafruitMotorShield AFMS = AdafruitMotorShield();
AdafruitStepperMotor* adafruit_stepper_motor = AFMS.getStepper(200, 2);
LightSensor carousel_calibration_sensor(A0);
StepperMotor stepper_motor(adafruit_stepper_motor, 200, StepperMotor::StepType::Microstep);
Carousel carousel(&stepper_motor, &carousel_calibration_sensor, 0.0);


void setup()
{
  AFMS.begin();
  Serial.begin(9600);
  //if (!carousel.start())
  //  Serial.println("carousel setup error");  
  carousel.setup();
}

void loop()
{
}
