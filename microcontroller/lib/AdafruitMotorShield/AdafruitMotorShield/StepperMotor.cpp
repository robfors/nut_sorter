/******************************************************************
 This is the library for the Adafruit Motor Shield V2 for Arduino. 
 It supports DC motors & Stepper motors with microstepping as well
 as stacking-support. It is *not* compatible with the V1 library!

 It will only work with https://www.adafruit.com/products/1483
 
 Adafruit invests time and resources providing this open
 source code, please support Adafruit and open-source hardware
 by purchasing products from Adafruit!
 
 Written by Limor Fried/Ladyada for Adafruit Industries.
 BSD license, check license.txt for more information.
 All text above must be included in any redistribution.
 ******************************************************************/

#include "AdafruitMotorShield.h"


#if (MICROSTEPS == 8)
uint8_t microstep_curve[] = {0, 50, 98, 142, 180, 212, 236, 250, 255};
#elif (MICROSTEPS == 16)
uint8_t microstep_curve[] = {0, 25, 50, 74, 98, 120, 141, 162, 180, 197, 212, 225, 236, 244, 250, 253, 255};
#endif


namespace AdafruitMotorShield
{
  
  StepperMotor::StepperMotor()
  {
    _current_step = 0;
    _pin_pwm_a = 0;
    _pin_in_a1 = 0;
    _pin_in_a2 = 0;
    _pin_pwm_b = 0;
    _pin_in_b1 = 0;
    _pin_in_b2 = 0;
  }
  
  
  void StepperMotor::release()
  {
    _pin_driver->set_pin_state(_pin_in_a1, LOW);
    _pin_driver->set_pin_state(_pin_in_a2, LOW);
    _pin_driver->set_pin_state(_pin_in_b1, LOW);
    _pin_driver->set_pin_state(_pin_in_b2, LOW);
    _pin_driver->set_pin_duty_cycle(_pin_pwm_a, 0);
    _pin_driver->set_pin_duty_cycle(_pin_pwm_b, 0);
  }
  
  
  uint8_t StepperMotor::step(uint8_t dir, uint8_t style)
  {
    uint8_t ocrb, ocra;
    
    ocra = ocrb = 255;
    
    // next determine what sort of stepping procedure we're up to
    if (style == SINGLE)
    {
      if ((_current_step/(MICROSTEPS/2)) % 2)
      {
        // we're at an odd step, weird
        if (dir == FORWARD)
          _current_step += MICROSTEPS/2;
        else
          _current_step -= MICROSTEPS/2;
      }
      else
      {
        // go to the next even step
        if (dir == FORWARD)
          _current_step += MICROSTEPS;
        else
          _current_step -= MICROSTEPS;
      }
    }
    else if (style == DOUBLE)
    {
      if (! (_current_step/(MICROSTEPS/2) % 2))
      {
        // we're at an even step, weird
        if (dir == FORWARD)
          _current_step += MICROSTEPS/2;
        else
          _current_step -= MICROSTEPS/2;
      }
      else
      {
        // go to the next odd step
        if (dir == FORWARD)
          _current_step += MICROSTEPS;
        else
          _current_step -= MICROSTEPS;
      }
    }
    else if (style == INTERLEAVE)
    {
      if (dir == FORWARD)
        _current_step += MICROSTEPS/2;
      else
        _current_step -= MICROSTEPS/2;
    } 
  
    if (style == MICROSTEP)
    {
      if (dir == FORWARD)
        _current_step++;
      else
        _current_step--;
      
      _current_step += MICROSTEPS*4;
      _current_step %= MICROSTEPS*4;
      
      ocra = ocrb = 0;
      //if ((_current_step >= 0) && (_current_step < MICROSTEPS))
      if (_current_step < MICROSTEPS)
      {
        ocra = microstep_curve[MICROSTEPS - _current_step];
        ocrb = microstep_curve[_current_step];
      }
      else if ((_current_step >= MICROSTEPS) && (_current_step < MICROSTEPS*2))
      {
        ocra = microstep_curve[_current_step - MICROSTEPS];
        ocrb = microstep_curve[MICROSTEPS*2 - _current_step];
      }
      else if ((_current_step >= MICROSTEPS*2) && (_current_step < MICROSTEPS*3))
      {
        ocra = microstep_curve[MICROSTEPS*3 - _current_step];
        ocrb = microstep_curve[_current_step - MICROSTEPS*2];
      }
      else if ((_current_step >= MICROSTEPS*3) && (_current_step < MICROSTEPS*4))
      {
        ocra = microstep_curve[_current_step - MICROSTEPS*3];
        ocrb = microstep_curve[MICROSTEPS*4 - _current_step];
      }
    }
    
    _current_step += MICROSTEPS*4;
    _current_step %= MICROSTEPS*4;
    
    _pin_driver->set_pin_duty_cycle(_pin_pwm_a, ocra*16);
    _pin_driver->set_pin_duty_cycle(_pin_pwm_b, ocrb*16);
    
    // release all
    uint8_t latch_state = 0; // all motor pins to 0
    
    if (style == MICROSTEP)
    {
      if ((_current_step >= 0) && (_current_step < MICROSTEPS))
        latch_state |= 0x03;
      if ((_current_step >= MICROSTEPS) && (_current_step < MICROSTEPS*2))
        latch_state |= 0x06;
      if ((_current_step >= MICROSTEPS*2) && (_current_step < MICROSTEPS*3))
        latch_state |= 0x0C;
      if ((_current_step >= MICROSTEPS*3) && (_current_step < MICROSTEPS*4))
        latch_state |= 0x09;
    }
    else
    {
      switch (_current_step/(MICROSTEPS/2))
      {
        case 0:
          latch_state |= 0x1; // energize coil 1 only
          break;
        case 1:
          latch_state |= 0x3; // energize coil 1+2
          break;
        case 2:
          latch_state |= 0x2; // energize coil 2 only
          break;
        case 3:
          latch_state |= 0x6; // energize coil 2+3
          break;
        case 4:
          latch_state |= 0x4; // energize coil 3 only
          break; 
        case 5:
          latch_state |= 0xC; // energize coil 3+4
          break;
        case 6:
          latch_state |= 0x8; // energize coil 4 only
          break;
        case 7:
          latch_state |= 0x9; // energize coil 1+4
          break;
      }
    }
    
    if (latch_state & 0x1)
      _pin_driver->set_pin_state(_pin_in_a2, HIGH);
    else
      _pin_driver->set_pin_state(_pin_in_a2, LOW);
    if (latch_state & 0x2)
      _pin_driver->set_pin_state(_pin_in_b1, HIGH);
    else
      _pin_driver->set_pin_state(_pin_in_b1, LOW);
    if (latch_state & 0x4)
      _pin_driver->set_pin_state(_pin_in_a1, HIGH);
    else
      _pin_driver->set_pin_state(_pin_in_a1, LOW);
    if (latch_state & 0x8)
      _pin_driver->set_pin_state(_pin_in_b2, HIGH);
    else
      _pin_driver->set_pin_state(_pin_in_b2, LOW);
  
    return _current_step;
  }
  
  
}
