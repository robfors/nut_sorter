#include "StepperMotor.h"


//
// public
//


StepperMotor::StepperMotor(AdafruitStepperMotor* motor, unsigned int num_steps, StepType step_type, boolean invert_direction)
: _step_timer(0, PeriodicTimer::Units::Microseconds)
{
  _current_step = 0;
  _direction = StepperMotor::Direction::Forward;
  _native_direction = FORWARD;
  _motor = motor;
  _is_direction_inverted = invert_direction;
  _is_turning = false;
  _step_type = step_type;
  _steps_to_turn = 0;
  
  switch (step_type)
  {
  case StepperMotor::StepType::Single:
    _native_step_type = SINGLE;
    _total_steps = num_steps;
    break;
  case StepperMotor::StepType::Double:
    _native_step_type = DOUBLE;
    _total_steps = num_steps;
    break;
  case StepperMotor::StepType::Interleave:
    _native_step_type = INTERLEAVE;
    _total_steps = num_steps;
    break;
  case StepperMotor::StepType::Microstep:
    _native_step_type = MICROSTEP;
    _total_steps = num_steps * MICROSTEPS;
    break;
  }
}


Angle StepperMotor::angle()
{
  return Angle::from_revolution((float)_current_step/_total_steps);
}


void StepperMotor::turn_to_angle(Angle angle, Direction direction, float speed)
{
  unsigned int step = round(angle.to_revolution() * _total_steps);
  turn_to_step(step, direction, speed);
}


void StepperMotor::turn_to_step(unsigned int step, Direction direction, float speed)
{
  unsigned int steps = 0;
  switch (_direction)
  {
  case StepperMotor::Direction::Forward:
    if (_current_step > step)
      step += _total_steps;
    steps = step - _current_step;
    break;
  case StepperMotor::Direction::Reverse:
    if (_current_step > step)
      steps = _current_step + _total_steps - step;
    else
      steps = _current_step - step;
    break;
  }
  turn_steps(steps, direction, speed);
}


void StepperMotor::reset_origin()
{
  _current_step = 0;
}


unsigned int StepperMotor::current_step()
{
  return _current_step;
}


void StepperMotor::tick()
{
  if (_is_turning && _step_timer.is_complete())
  {
    _motor->onestep(_native_direction, _native_step_type);
    
    switch (_direction)
    {
    case StepperMotor::Direction::Forward:
      if (_current_step == _total_steps-1)
        _current_step = 0;
      else
        _current_step++;
      break;
    case StepperMotor::Direction::Reverse:
      if (_current_step == 0)
        _current_step = _total_steps-1;
      else
        _current_step--;
      break;
    }
    if(_steps_to_turn != 0)
    {
      _steps_to_turn--;
      if(_steps_to_turn == 0)
        stop();
    }
    
    _step_timer.increment_interval();
  }
}


void StepperMotor::stop()
{
  _is_turning = false;
  _steps_to_turn = 0;
}


boolean StepperMotor::is_stopped()
{
  return !is_turning();
}


void StepperMotor::turn(Direction direction, float speed)
{
  _start(0, direction, speed);
}


void StepperMotor::turn_angle(Angle angle, Direction direction, float speed)
{
  unsigned int steps = round(angle.to_revolution() * _total_steps);
  turn_steps(steps, direction, speed);
}


void StepperMotor::turn_steps(unsigned long steps, Direction direction, float speed)
{
  if (steps == 0)
  {
    stop();
    return;
  }
  _start(steps, direction, speed);
}


boolean StepperMotor::is_turning()
{
  return _is_turning;
}


//
// private
//


void StepperMotor::_setup_speed(float speed)
{
  //speed; //rpm
  float step_time = 1/speed; // m per rev
  step_time = step_time * 60000000; // us per rev
  step_time = step_time / _total_steps; // us per step
  _step_timer = PeriodicTimer((unsigned long)step_time, PeriodicTimer::Units::Microseconds);
}


void StepperMotor::_start(unsigned long steps, Direction direction, float speed)
{
  stop();
  _steps_to_turn = steps;
  _setup_speed(speed);
  _direction = direction;
  switch (direction)
  {
  case StepperMotor::Direction::Forward:
    if (_is_direction_inverted)
      _native_direction = BACKWARD;
    else
      _native_direction = FORWARD;
    break;
  case StepperMotor::Direction::Reverse:
    if (_is_direction_inverted)
      _native_direction = FORWARD;
    else
      _native_direction = BACKWARD;
    break;
  }
  _is_turning = true;
  _step_timer.reset();
}
