#include <Arduino.h>
#include <Wire.h>
#include <HMC5883L.h>
#include <Timer.h>
#include <FerromagneticSensor.h>

FerromagneticSensor ferromagnetic_sensor;

void setup()
{
  Serial.begin(9600);
  if (!ferromagnetic_sensor.setup())
    Serial.println("ferromagnetic sensor setup error");  
}

void loop()
{
  for (int i = 0; i < 100; i++)
  {
    //ferromagnetic_sensor.tick();
    delay(10);
  }
  Serial.println(ferromagnetic_sensor.is_ferromagnetic_material_present());
  Serial.println(ferromagnetic_sensor.field());
  delay(100);
}
