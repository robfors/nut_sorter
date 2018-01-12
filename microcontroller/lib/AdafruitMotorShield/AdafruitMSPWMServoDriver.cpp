/*************************************************** 
  This is a library for our Adafruit 16-channel PWM & Servo driver

  Pick one up today in the adafruit shop!
  ------> http://www.adafruit.com/products/815

  These displays use I2C to communicate, 2 pins are required to  
  interface. For Arduino UNOs, thats SCL -> Analog 5, SDA -> Analog 4

  Adafruit invests time and resources providing this open source code, 
  please support Adafruit and open-source hardware by purchasing 
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.  
  BSD license, all text above must be included in any redistribution
 ****************************************************/

#include <Wire.h>

#include "AdafruitMotorShield.h"


AdafruitMSPWMServoDriver::AdafruitMSPWMServoDriver(uint8_t addr)
{
  _i2caddr = addr;
}

void AdafruitMSPWMServoDriver::begin(void)
{
  Wire.begin();
  reset();
}


void AdafruitMSPWMServoDriver::reset(void)
{
  write8(PCA9685_MODE1, 0x0);
}


void AdafruitMSPWMServoDriver::setPWMFreq(float freq)
{
  freq *= 0.9;  // Correct for overshoot in the frequency setting (see issue #11).
  
  float prescaleval = 25000000;
  prescaleval /= 4096;
  prescaleval /= freq;
  prescaleval -= 1;
  uint8_t prescale = floor(prescaleval + 0.5);
  
  uint8_t oldmode = read8(PCA9685_MODE1);
  uint8_t newmode = (oldmode&0x7F) | 0x10; // sleep
  write8(PCA9685_MODE1, newmode); // go to sleep
  write8(PCA9685_PRESCALE, prescale); // set the prescaler
  write8(PCA9685_MODE1, oldmode);
  delay(5);
  write8(PCA9685_MODE1, oldmode | 0xa1);  //  This sets the MODE1 register to turn on auto increment.
                                          // This is why the beginTransmission below was not working.
  //  Serial.print("Mode now 0x"); Serial.println(read8(PCA9685_MODE1), HEX);
}


void AdafruitMSPWMServoDriver::setPWM(uint8_t num, uint16_t on, uint16_t off)
{
  //Serial.print("Setting PWM "); Serial.print(num); Serial.print(": "); Serial.print(on); Serial.print("->"); Serial.println(off);

  Wire.beginTransmission(_i2caddr);
  #if ARDUINO >= 100
    Wire.write(LED0_ON_L+4*num);
    Wire.write(on);
    Wire.write(on>>8);
    Wire.write(off);
    Wire.write(off>>8);
  #else
    Wire.send(LED0_ON_L+4*num);
    Wire.send((uint8_t)on);
    Wire.send((uint8_t)(on>>8));
    Wire.send((uint8_t)off);
    Wire.send((uint8_t)(off>>8));
  #endif
  Wire.endTransmission();
}


uint8_t AdafruitMSPWMServoDriver::read8(uint8_t addr)
{
  Wire.beginTransmission(_i2caddr);
  #if ARDUINO >= 100
    Wire.write(addr);
  #else
    Wire.send(addr);
  #endif
  Wire.endTransmission();
  
  Wire.requestFrom((uint8_t)_i2caddr, (uint8_t)1);
  #if ARDUINO >= 100
    return Wire.read();
  #else
    return Wire.receive();
  #endif
}


void AdafruitMSPWMServoDriver::write8(uint8_t addr, uint8_t d)
{
  Wire.beginTransmission(_i2caddr);
  #if ARDUINO >= 100
    Wire.write(addr);
    Wire.write(d);
  #else
    Wire.send(addr);
    Wire.send(d);
  #endif
  Wire.endTransmission();
}
