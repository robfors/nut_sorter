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


#if (MICROSTEPS == 8)
uint8_t microstepcurve[] = {0, 50, 98, 142, 180, 212, 236, 250, 255};
#elif (MICROSTEPS == 16)
uint8_t microstepcurve[] = {0, 25, 50, 74, 98, 120, 141, 162, 180, 197, 212, 225, 236, 244, 250, 253, 255};
#endif


AdafruitStepperMotor::AdafruitStepperMotor(void)
{
  revsteps = steppernum = currentstep = 0;
}


void AdafruitStepperMotor::setSpeed(uint16_t rpm)
{
  usperstep = 60000000 / ((uint32_t)revsteps * (uint32_t)rpm);
}


void AdafruitStepperMotor::release(void)
{
  MC->setPin(AIN1pin, LOW);
  MC->setPin(AIN2pin, LOW);
  MC->setPin(BIN1pin, LOW);
  MC->setPin(BIN2pin, LOW);
  MC->setPWM(PWMApin, 0);
  MC->setPWM(PWMBpin, 0);
}


void AdafruitStepperMotor::step(uint16_t steps, uint8_t dir,  uint8_t style)
{
  uint32_t uspers = usperstep;
  uint8_t ret = 0;
  
  if (style == INTERLEAVE)
    uspers /= 2;
  else if (style == MICROSTEP)
  {
    uspers /= MICROSTEPS;
    steps *= MICROSTEPS;
  }
  
  while (steps--)
  {
    ret = onestep(dir, style);
    delayMicroseconds(uspers);
    yield(); // required for ESP8266
  }
}


uint8_t AdafruitStepperMotor::onestep(uint8_t dir, uint8_t style)
{
  uint8_t a, b, c, d;
  uint8_t ocrb, ocra;
  
  ocra = ocrb = 255;
  
  // next determine what sort of stepping procedure we're up to
  if (style == SINGLE)
  {
    if ((currentstep/(MICROSTEPS/2)) % 2)
    {
      // we're at an odd step, weird
      if (dir == FORWARD)
        currentstep += MICROSTEPS/2;
      else
        currentstep -= MICROSTEPS/2;
    }
    else
    {
      // go to the next even step
      if (dir == FORWARD)
        currentstep += MICROSTEPS;
      else
        currentstep -= MICROSTEPS;
    }
  }
  else if (style == DOUBLE)
  {
    if (! (currentstep/(MICROSTEPS/2) % 2))
    {
      // we're at an even step, weird
      if (dir == FORWARD)
        currentstep += MICROSTEPS/2;
      else
        currentstep -= MICROSTEPS/2;
    }
    else
    {
      // go to the next odd step
      if (dir == FORWARD)
        currentstep += MICROSTEPS;
      else
        currentstep -= MICROSTEPS;
    }
  }
  else if (style == INTERLEAVE)
  {
    if (dir == FORWARD)
      currentstep += MICROSTEPS/2;
    else
      currentstep -= MICROSTEPS/2;
  } 

  if (style == MICROSTEP)
  {
    if (dir == FORWARD)
      currentstep++;
    else
      currentstep--;
    
    currentstep += MICROSTEPS*4;
    currentstep %= MICROSTEPS*4;
    
    ocra = ocrb = 0;
    if ((currentstep >= 0) && (currentstep < MICROSTEPS))
    {
      ocra = microstepcurve[MICROSTEPS - currentstep];
      ocrb = microstepcurve[currentstep];
    }
    else if ((currentstep >= MICROSTEPS) && (currentstep < MICROSTEPS*2))
    {
      ocra = microstepcurve[currentstep - MICROSTEPS];
      ocrb = microstepcurve[MICROSTEPS*2 - currentstep];
    }
    else if ((currentstep >= MICROSTEPS*2) && (currentstep < MICROSTEPS*3))
    {
      ocra = microstepcurve[MICROSTEPS*3 - currentstep];
      ocrb = microstepcurve[currentstep - MICROSTEPS*2];
    }
    else if ((currentstep >= MICROSTEPS*3) && (currentstep < MICROSTEPS*4))
    {
      ocra = microstepcurve[currentstep - MICROSTEPS*3];
      ocrb = microstepcurve[MICROSTEPS*4 - currentstep];
    }
  }
  
  currentstep += MICROSTEPS*4;
  currentstep %= MICROSTEPS*4;
  
  MC->setPWM(PWMApin, ocra*16);
  MC->setPWM(PWMBpin, ocrb*16);
  
  // release all
  uint8_t latch_state = 0; // all motor pins to 0
  
  if (style == MICROSTEP)
  {
    if ((currentstep >= 0) && (currentstep < MICROSTEPS))
      latch_state |= 0x03;
    if ((currentstep >= MICROSTEPS) && (currentstep < MICROSTEPS*2))
      latch_state |= 0x06;
    if ((currentstep >= MICROSTEPS*2) && (currentstep < MICROSTEPS*3))
      latch_state |= 0x0C;
    if ((currentstep >= MICROSTEPS*3) && (currentstep < MICROSTEPS*4))
      latch_state |= 0x09;
  }
  else
  {
    switch (currentstep/(MICROSTEPS/2))
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
    MC->setPin(AIN2pin, HIGH);
  else
    MC->setPin(AIN2pin, LOW);
  if (latch_state & 0x2)
    MC->setPin(BIN1pin, HIGH);
  else
    MC->setPin(BIN1pin, LOW);
  if (latch_state & 0x4)
    MC->setPin(AIN1pin, HIGH);
  else
    MC->setPin(AIN1pin, LOW);
  if (latch_state & 0x8)
    MC->setPin(BIN2pin, HIGH);
  else
    MC->setPin(BIN2pin, LOW);

  return currentstep;
}

