#include <Arduino.h>
#include <Wire.h>
#include <Servo.h>

#include "NutSorter/NutSorter.h"


// setup every task (eg. pin modes)
// some return false to indicate an error
void setup()
{
  Serial.begin(9600);
  Serial.println("|reset");
  Serial.println("calibrating...");
  Serial.println("|calibrating");
  NutSorter::Main::setup();
  delay(5000);
  Serial.println("ready...");
  Serial.println("|running");
  NutSorter::Main::start();
}


// this is the reactor loop
// no calls should block here!
// if they do, all other tasks will miss deadlines
// the tick() method is called for each task
//    often the task will simply return
//    sometimes the task will have work do to, it will quickly run and return
//    execution to the ractor loop for the next task
void loop()
{
  NutSorter::Main::tick();
}
