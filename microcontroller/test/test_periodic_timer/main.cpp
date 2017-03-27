#include <Arduino.h>
#include <PeriodicTimer.h>

PeriodicTimer periodic_timer(1000, PeriodicTimer::Units::Milliseconds);

void setup()
{
  Serial.begin(9600);
  periodic_timer.reset();
}

void loop()
{
  while (periodic_timer.is_pending())
  {}
  Serial.print('.');
  periodic_timer.update_interval();
  delay(3000);
  Serial.print(periodic_timer.was_interval_missed());
}
