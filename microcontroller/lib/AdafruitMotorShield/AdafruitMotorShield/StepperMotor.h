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

#ifndef _ADAFRUIT_MOTTRSHIELD_STEPPER_MOTOR_H_
#define _ADAFRUIT_MOTTRSHIELD_STEPPER_MOTOR_H_


namespace AdafruitMotorShield
{
  
  class StepperMotor
  {
    friend class Shield;  
    
    public:
    
    StepperMotor();
    
    uint8_t step(uint8_t dir, uint8_t style);
    void release();
    
    private:
    
    uint8_t _pin_pwm_a, _pin_in_a1, _pin_in_a2;
    uint8_t _pin_pwm_b, _pin_in_b1, _pin_in_b2;
    uint8_t _current_step;
    PinDriver* _pin_driver;
    
  };
  
}

#endif
