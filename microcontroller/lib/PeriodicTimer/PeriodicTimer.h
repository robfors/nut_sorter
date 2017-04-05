#ifndef _PERIODIC_TIMER_H_
#define _PERIODIC_TIMER_H_

/* Use this to setup delays without blocking.
 * 
 * This differs from using the Timer class as the timer will be consistent
 * by incrementing the stop time rather that starting a new timer when we
 * find out that the old one has completed.
 */


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
