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

#ifndef _ADAFRUIT_MOTTR_SHIELD_SHIELD_H_
#define _ADAFRUIT_MOTTR_SHIELD_SHIELD_H_


namespace AdafruitMotorShield
{
  
  class Shield
  {
    
    friend class DCMotor;
    friend class StepperMotor;
    
    public:
    
    Shield(uint8_t ic2_address = 0x60);
    
    void begin(uint16_t frequency = 1600);
    DCMotor* get_dc_motor(uint8_t n);
    StepperMotor* get_stepper_motor(uint8_t n);
    
    private:
    
    DCMotor* dc_motors[4];
    StepperMotor* stepper_motors[2];
    PinDriver _pin_driver;
    
  };
  
}

#endif
