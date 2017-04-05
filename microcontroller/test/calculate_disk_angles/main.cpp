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


AdafruitMotorShield AFMS = AdafruitMotorShield();
AdafruitStepperMotor* adafruit_stepper_motor = AFMS.getStepper(200, 2);
StepperMotor stepper_motor(adafruit_stepper_motor, 200, StepperMotor::StepType::Microstep, false);
Carousel carousel(&stepper_motor, Angle(66.5));


void setup()
{
  AFMS.begin();
  Serial.begin(9600);
  carousel.setup();
  Serial.println("calibrated...");
  Serial.println("enter angle: ");
}

void loop()
{
  stepper_motor.tick();
  
  if (stepper_motor.is_stopped() && Serial.available() > 0)
  {
    float angle = Serial.parseFloat();
    Serial.print("moving to ");
    Serial.println(angle);
    stepper_motor.turn_to_angle(angle, StepperMotor::Direction::Forward, 4.0);
  }
}
