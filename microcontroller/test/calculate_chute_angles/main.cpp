#include <Arduino.h>
#include <Wire.h>

#include "Angle.h"
#include "Math.h"
#include "VarSpeedServo.h"
#include "Servo.h"

Servo servo(9, Angle(90.0));

void setup()
{
  Serial.begin(9600);
  servo.setup();
  Serial.println("enter angle: ");
}

void loop()
{
  if (Serial.available() > 0)
  {
    unsigned int angle = Serial.parseInt();
    Serial.print("moving to ");
    Serial.println(angle);
    servo.turn_to_angle(Angle(angle));
  }
}
