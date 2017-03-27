#include <Arduino.h>

#include "ForceSensor.h"

ForceSensor force_sensor(A0);

void setup()
{
  Serial.begin(9600);
  force_sensor.setup();
}

void loop()
{
  Serial.println("test");
  Serial.println(force_sensor.is_depressed());
  delay(100);
}
