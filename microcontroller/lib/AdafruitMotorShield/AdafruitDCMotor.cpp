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


#include <Arduino.h>
#include <Wire.h>

#include "AdafruitMotorShield.h"


AdafruitDCMotor::AdafruitDCMotor(void)
{
  MC = NULL;
  motornum = 0;
  PWMpin = IN1pin = IN2pin = 0;
}


void AdafruitDCMotor::run(uint8_t cmd)
{
  switch (cmd)
  {
    case FORWARD:
      MC->setPin(IN2pin, LOW);  // take low first to avoid 'break'
      MC->setPin(IN1pin, HIGH);
      break;
    case BACKWARD:
      MC->setPin(IN1pin, LOW);  // take low first to avoid 'break'
      MC->setPin(IN2pin, HIGH);
      break;
    case RELEASE:
      MC->setPin(IN1pin, LOW);
      MC->setPin(IN2pin, LOW);
      break;
  }
}


void AdafruitDCMotor::setSpeed(uint8_t speed)
{
  MC->setPWM(PWMpin, speed*16);
}
