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


AdafruitMotorShield::AdafruitMotorShield(uint8_t addr)
{
  _addr = addr;
  _pwm = AdafruitMSPWMServoDriver(_addr);
}


void AdafruitMotorShield::begin(uint16_t freq)
{
  // init PWM w/_freq
  Wire.begin();
  _pwm.begin();
  _freq = freq;
  _pwm.setPWMFreq(_freq);  // This is the maximum PWM frequency
  for (uint8_t i = 0; i < 16; i++) 
    _pwm.setPWM(i, 0, 0);
}


void AdafruitMotorShield::setPWM(uint8_t pin, uint16_t value)
{
  if (value > 4095)
    _pwm.setPWM(pin, 4096, 0);
  else 
    _pwm.setPWM(pin, 0, value);
}


void AdafruitMotorShield::setPin(uint8_t pin, boolean value)
{
  if (value == LOW)
    _pwm.setPWM(pin, 0, 0);
  else
    _pwm.setPWM(pin, 4096, 0);
}


AdafruitDCMotor *AdafruitMotorShield::getMotor(uint8_t num)
{
  if (num > 4) return NULL;
  
  num--;
  
  if (dcmotors[num].motornum == 0)
  {
    // not init'd yet!
    dcmotors[num].motornum = num;
    dcmotors[num].MC = this;
    uint8_t pwm, in1, in2;
    switch (num)
    {
      case 0:
        pwm = 8; in2 = 9; in1 = 10;
        break;
      case 1:
        pwm = 13; in2 = 12; in1 = 11;
        break;
      case 2:
        pwm = 2; in2 = 3; in1 = 4;
        break;
      case 3:
        pwm = 7; in2 = 6; in1 = 5;
        break;
    }
    dcmotors[num].PWMpin = pwm;
    dcmotors[num].IN1pin = in1;
    dcmotors[num].IN2pin = in2;
  }
  return &dcmotors[num];
}


AdafruitStepperMotor *AdafruitMotorShield::getStepper(uint16_t steps, uint8_t num)
{
  if (num > 2) return NULL;

  num--;

  if (steppers[num].steppernum == 0)
  {
    // not init'd yet!
    steppers[num].steppernum = num;
    steppers[num].revsteps = steps;
    steppers[num].MC = this;
    uint8_t pwma, pwmb, ain1, ain2, bin1, bin2;
    switch (num)
    {
      case 0:
        pwma = 8; ain2 = 9; ain1 = 10;
        pwmb = 13; bin2 = 12; bin1 = 11;
        break;
      case 1:
        pwma = 2; ain2 = 3; ain1 = 4;
        pwmb = 7; bin2 = 6; bin1 = 5;
        break;
    }
    steppers[num].PWMApin = pwma;
    steppers[num].PWMBpin = pwmb;
    steppers[num].AIN1pin = ain1;
    steppers[num].AIN2pin = ain2;
    steppers[num].BIN1pin = bin1;
    steppers[num].BIN2pin = bin2;
  }
  return &steppers[num];
}
