#ifndef _PERIODIC_TIMER_H_
#define _PERIODIC_TIMER_H_

#include <Arduino.h>


class PeriodicTimer
{
  
  public:
  
  enum class Units { Microseconds, Milliseconds, Seconds };
  
  PeriodicTimer(unsigned long interval_length, Units units);
  
  void increment_interval();
  boolean is_complete();
  boolean is_pending();
  void reset();
  void update_interval();
  boolean was_interval_missed();
  
  private:
  
  unsigned long _interval_length;
  unsigned long _next_interval;
  Units _units;
  
  unsigned long _current_time();
  
};

#endif
