#include <Arduino.h>
#include <Timer.h>
#include <ConductivitySensor.h>

int pins[] = {5, 6, 7};

ConductivitySensor conductivity_sensor(pins, 3);

void setup()
{
  Serial.begin(9600);
  if (!conductivity_sensor.setup())
    Serial.println("conductivity sensor setup error");  
}

void loop()
{
  Serial.println("measure");
  conductivity_sensor.measure();
  while (!conductivity_sensor.is_result_ready())
  {
    conductivity_sensor.tick();
  }
  Serial.println(conductivity_sensor.result());
  delay(50);
}
