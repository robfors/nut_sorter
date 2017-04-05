#ifndef _TIMER_H_
#define _TIMER_H_

// Use this to setup delays without blocking.

#include <Arduino.h>


class Timer
{
  
  public:
  
  enum class Units { Microseconds, Milliseconds, Seconds };
  
  Timer(Units units);
  Timer(unsigned long default_length, Units units);
  
  boolean is_complete();
  boolean is_running();
  void start();
  void start(unsigned long length);
  void stop();
  
  private:
  
  unsigned long _default_length;
  boolean _is_active;
  unsigned long _length;
  unsigned long _start_time;
  Units _units;
  
  unsigned long _current_time();
  void _update();
  
};

#endif
