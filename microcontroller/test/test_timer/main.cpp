#include <Arduino.h>
#include <Timer.h>

Timer timer(Timer::Units::Seconds);

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  timer.start(2);
  while (timer.is_pending())
  {}
  Serial.print('.');
  delay(50);
}
