#include "PeriodicTimer.h"


//
// public
//


PeriodicTimer::PeriodicTimer(unsigned long interval_length, Units units)
{
  _interval_length = interval_length;
  _units = units;
  _next_interval = _current_time() + _interval_length;
}


void PeriodicTimer::increment_interval()
{
  _next_interval += _interval_length;
}


boolean PeriodicTimer::is_complete()
{
  return !is_pending();
}


boolean PeriodicTimer::is_pending()
{
  return _current_time() < _next_interval;
}


void PeriodicTimer::reset()
{
  _next_interval = _current_time() + _interval_length;
}


void PeriodicTimer::update_interval()
{
  int steps = (_current_time() - _next_interval) / _interval_length + 1;
  _next_interval += _interval_length*steps;
}


boolean PeriodicTimer::was_interval_missed()
{
  return _current_time() >= _next_interval + _interval_length;
}


//
// private
//


unsigned long PeriodicTimer::_current_time()
{
  switch (_units)
  {
  case PeriodicTimer::Units::Microseconds:
    return micros();
    break;
  case PeriodicTimer::Units::Milliseconds:
    return millis();
    break;
  case PeriodicTimer::Units::Seconds:
    return millis()/1000;
    break;
  }
  return 0;
}
