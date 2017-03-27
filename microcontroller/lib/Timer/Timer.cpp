#include "Timer.h"


//
// public
//


Timer::Timer(Units units)
{
  _default_length = 0;
  _length = 0;
  _units = units;
  _is_active = false;
  _start_time = 0;
}


Timer::Timer(unsigned long default_length, Units units)
{
  _default_length = default_length;
  _length = 0;
  _units = units;
  _is_active = false;
  _start_time = 0;
}


boolean Timer::is_complete()
{
  return !is_running();
}


boolean Timer::is_running()
{
  _update();
  return _is_active;
}


void Timer::start()
{
  _start_time = _current_time(); // save time first
  if (_default_length == 0)
  {
    _start_time = 0;
    return;
  }
  _length = _default_length;
  _is_active = true;
}


void Timer::start(unsigned long length)
{
  _start_time = _current_time(); // save time first
  _length = length;
  _is_active = true;
}


void Timer::stop()
{
  _start_time = 0;
  _length = 0;
  _is_active = false;  
}


//
// private
//


unsigned long Timer::_current_time()
{
  switch (_units)
  {
  case Timer::Units::Microseconds:
    return micros();
    break;
  case Timer::Units::Milliseconds:
    return millis();
    break;
  case Timer::Units::Seconds:
    return millis()/1000;
    break;
  }
  return 0;
}


void Timer::_update()
{
  if (_is_active && _current_time() >= _start_time + _length)
    _is_active = false;
}
