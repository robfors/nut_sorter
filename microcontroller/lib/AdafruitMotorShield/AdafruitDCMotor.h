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

#ifndef _ADAFRUIT_MOTTRSHIELD_DC_MOTOR_H_
#define _ADAFRUIT_MOTTRSHIELD_DC_MOTOR_H_

#include <inttypes.h>
#include <Wire.h>

class AdafruitDCMotor
{
  
  public:
  
  AdafruitDCMotor(void);
  friend class AdafruitMotorShield;
  void run(uint8_t);
  void setSpeed(uint8_t);
  
  private:
  
  uint8_t PWMpin, IN1pin, IN2pin;
  AdafruitMotorShield* MC;
  uint8_t motornum;
  
};

#endif
