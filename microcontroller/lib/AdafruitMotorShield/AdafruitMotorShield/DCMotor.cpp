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
  
  DCMotor::DCMotor()
  {
    _pin_driver = NULL;
    _pin_pwm = 0;
    _pin_in_1 = 0;
    _pin_in_2 = 0;
  }
  
  
  void DCMotor::run(uint8_t cmd)
  {
    switch (cmd)
    {
      case FORWARD:
        _pin_driver->set_pin_state(_pin_in_2, LOW);  // take low first to avoid 'break'
        _pin_driver->set_pin_state(_pin_in_1, HIGH);
        break;
      case BACKWARD:
        _pin_driver->set_pin_state(_pin_in_1, LOW);  // take low first to avoid 'break'
        _pin_driver->set_pin_state(_pin_in_2, HIGH);
        break;
      case RELEASE:
        _pin_driver->set_pin_state(_pin_in_1, LOW);
        _pin_driver->set_pin_state(_pin_in_2, LOW);
        break;
    }
  }
  
  
  void DCMotor::set_speed(uint8_t speed)
  {
    _pin_driver->set_pin_duty_cycle(_pin_pwm, speed * 16);
  }

}
