#ifndef _STEPPERMOTOR_H_
#define _STEPPERMOTOR_H_

/* This class abstracts the functionality of a stepper motor.
 * 
 * We use this to conveniently turn angles specified while keeping track
 * of its positon.
 * 
 * This class is a task. As such the 'tick()' method must be called
 * often to ensure we dont miss sending any steps to the motor shield,
 * causing the motor to become out of sync with the postion we are tracking.
 */

#include <Arduino.h>
#include <Wire.h>

#include "Math.h"
#include "AdafruitMotorShield.h"
#include "PeriodicTimer.h"
#include "Angle.h"


class StepperMotor
{
  
  public:
  
  enum class Direction { Forward, Reverse };
  enum class StepType { Single, Double, Interleave, Microstep };
  
  StepperMotor(AdafruitStepperMotor* motor, unsigned int num_steps, StepType step_type, boolean invert_direction);
  
  Angle angle();
  void turn_to_angle(Angle angle, Direction direction, float speed);
  void turn_to_step(unsigned int step, Direction direction, float speed);
  void reset_origin();
  unsigned int current_step();
  void stop();
  boolean is_stopped();
  void tick();
  void turn(Direction direction, float speed);
  void turn_angle(Angle angle, Direction direction, float speed);
  void turn_steps(unsigned long steps, Direction direction, float speed);
  boolean is_turning();
  
  private:
  
  unsigned int _current_step;
  Direction _direction;
  AdafruitStepperMotor* _motor;
  int _native_step_type;
  int _native_direction; 
  boolean _is_direction_inverted;
  boolean _is_turning;
  PeriodicTimer _step_timer;
  StepType _step_type;
  unsigned long _steps_to_turn;
  unsigned int _total_steps;
  
  void _setup_speed(float speed);
  void _start(unsigned long steps, Direction direction, float speed);
  
};

#endif
