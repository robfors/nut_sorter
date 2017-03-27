#include <Arduino.h>

#include "LightSensor.h"

LightSensor light_sensor(A0);

void setup()
{
  Serial.begin(9600);
  light_sensor.setup();
}

void loop()
{
  Serial.println(light_sensor.is_lit());
  delay(100);
}
