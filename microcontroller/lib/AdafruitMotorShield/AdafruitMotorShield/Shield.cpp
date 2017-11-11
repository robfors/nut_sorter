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


namespace AdafruitMotorShield
{
  
  
  Shield::Shield(uint8_t ic2_address)
  {
    _pin_driver = PinDriver(ic2_address);
  }
  
  
  void Shield::begin(uint16_t frequency)
  {
    // init PWM w/_frequency
    Wire.begin();
    _pin_driver.begin();
    _pin_driver.set_pwm_frequency(frequency);  // This is the maximum PWM frequency
    for (uint8_t i = 0; i < 16; i++) 
      _pin_driver.set_pin_state(i, LOW);
  }
  
  
  DCMotor* Shield::get_dc_motor(uint8_t num)
  {
    num--;
    uint8_t pin_pwm, pin_in_1, pin_in_2;
    switch (num)
    {
      case 0:
        pin_pwm = 8; pin_in_1 = 10; pin_in_2 = 9;
        break;
      case 1:
        pin_pwm = 13; pin_in_1 = 11; pin_in_2 = 12;
        break;
      case 2:
        pin_pwm = 2; pin_in_1 = 4; pin_in_2 = 3;
        break;
      case 3:
        pin_pwm = 7; pin_in_1 = 5; pin_in_2 = 6;
        break;
      default:
        return NULL;
    }
    
    if (stepper_motors[num/2] != NULL) return NULL; // ports already in use
    
    if (dc_motors[num] == NULL)
    {
      DCMotor* new_dc_motor = new DCMotor;
      if (new_dc_motor == NULL) return NULL; // memory error
      
      new_dc_motor->_pin_driver = &_pin_driver;
      new_dc_motor->_pin_pwm = pin_pwm;
      new_dc_motor->_pin_in_1 = pin_in_1;
      new_dc_motor->_pin_in_2 = pin_in_2;
      
      dc_motors[num] = new_dc_motor;
    }
    
    return dc_motors[num];
  }
  
  
  StepperMotor* Shield::get_stepper_motor(uint8_t num)
  {
    num--;
    uint8_t pin_pwm_a, pin_pwm_b, pin_in_a1, pin_in_a2, pin_in_b1, pin_in_b2;
    switch (num)
    {
      case 0:
        pin_pwm_a = 8; pin_in_a1 = 10; pin_in_a2 = 9;
        pin_pwm_b = 13; pin_in_b1 = 11; pin_in_b2 = 12;
        break;
      case 1:
        pin_pwm_a = 2; pin_in_a1 = 4; pin_in_a2 = 3;
        pin_pwm_b = 7; pin_in_b1 = 5; pin_in_b2 = 6;
        break;
      default:
        return NULL;
    }
    
    if (dc_motors[num * 2] != NULL || dc_motors[(num * 2) + 1] != NULL) return NULL; // ports already in use
    
    if (stepper_motors[num] == NULL)
    {
      StepperMotor* new_stepper_motor = new StepperMotor;
      if (new_stepper_motor == NULL) return NULL; // memory error
      
      new_stepper_motor->_pin_driver = &_pin_driver;
      new_stepper_motor->_pin_pwm_a = pin_pwm_a;
      new_stepper_motor->_pin_pwm_b = pin_pwm_b;
      new_stepper_motor->_pin_in_a1 = pin_in_a1;
      new_stepper_motor->_pin_in_a2 = pin_in_a2;
      new_stepper_motor->_pin_in_b1 = pin_in_b1;
      new_stepper_motor->_pin_in_b2 = pin_in_b2;
      
      stepper_motors[num] = new_stepper_motor;
    }
    
    return stepper_motors[num];
  }
  
  
}
