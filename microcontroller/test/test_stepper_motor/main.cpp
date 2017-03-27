#include <Arduino.h>
#include <Wire.h>

#include "AdafruitMotorShield.h"
#include "Math.h"

#include "PeriodicTimer.h"
#include "StepperMotor.h"

AdafruitMotorShield AFMS = AdafruitMotorShield();
AdafruitStepperMotor* motor = AFMS.getStepper(200, 2);

StepperMotor stepper_motor(motor, 200, StepperMotor::StepType::Microstep, false);

void setup()
{
  AFMS.begin();
  Serial.begin(9600);
  //stepper_motor.turn(StepperMotor::Direction::Forward, 4.0);
  stepper_motor.turn_angle(90.0, StepperMotor::Direction::Forward, 4.0);
}

void loop()
{
  stepper_motor.tick();
}
