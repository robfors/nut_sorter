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

#include "AdafruitMotorShield.h"


namespace AdafruitMotorShield
{
  
  
  //
  // public
  //
  
  
  PinDriver::PinDriver(uint8_t ic2_address)
  {
    _ic2_address = ic2_address;
  }
  
  
  void PinDriver::begin()
  {
    Wire.begin();
    reset();
  }
  
  
  void PinDriver::reset()
  {
    _write8(PCA9685_MODE1, 0x0);
  }
  
  
  void PinDriver::set_pwm_frequency(float frequency)
  {
    frequency *= 0.9;  // Correct for overshoot in the frequency setting (see issue #11).
    
    float prescale_val = 25000000;
    prescale_val /= 4096;
    prescale_val /= frequency;
    prescale_val -= 1;
    uint8_t prescale = floor(prescale_val + 0.5);
    
    uint8_t old_mode = _read8(PCA9685_MODE1);
    uint8_t new_mode = (old_mode & 0x7F) | 0x10; // sleep
    _write8(PCA9685_MODE1, new_mode); // go to sleep
    _write8(PCA9685_PRESCALE, prescale); // set the prescaler
    _write8(PCA9685_MODE1, old_mode);
    delay(5);
    _write8(PCA9685_MODE1, old_mode | 0xa1);  //  This sets the MODE1 register to turn on auto increment.
                                            // This is why the beginTransmission below was not working.
    //  Serial.print("Mode now 0x"); Serial.println(read8(PCA9685_MODE1), HEX);
  }
  
  
  void PinDriver::set_pin_duty_cycle(uint8_t pin, uint16_t value)
  {
    if (value > 4095)
      _set_pin_pwm_phases(pin, 4096, 0);
    else 
      _set_pin_pwm_phases(pin, 0, value);
  }
  
  
  void PinDriver::set_pin_state(uint8_t pin, boolean value)
  {
    if (value == LOW)
      _set_pin_pwm_phases(pin, 0, 0);
    else
      _set_pin_pwm_phases(pin, 4096, 0);
  }
  
    
  //
  // private
  //
  
  
  void PinDriver::_set_pin_pwm_phases(uint8_t num, uint16_t phase_begin, uint16_t phase_end)
  {
    Wire.beginTransmission(_ic2_address);
    #if ARDUINO >= 100
      Wire.write(LED0_ON_L + 4 * num);
      Wire.write(phase_begin);
      Wire.write(phase_begin >> 8);
      Wire.write(phase_end);
      Wire.write(phase_end >> 8);
    #else
      Wire.send(LED0_ON_L + 4 * num);
      Wire.send((uint8_t)phase_begin);
      Wire.send((uint8_t)(phase_begin >> 8));
      Wire.send((uint8_t)phase_end);
      Wire.send((uint8_t)(phase_end >> 8));
    #endif
    Wire.endTransmission();
  }
  
  
  uint8_t PinDriver::_read8(uint8_t addr)
  {
    Wire.beginTransmission(_ic2_address);
    #if ARDUINO >= 100
      Wire.write(addr);
    #else
      Wire.send(addr);
    #endif
    Wire.endTransmission();
    
    Wire.requestFrom((uint8_t)_ic2_address, (uint8_t)1);
    #if ARDUINO >= 100
      return Wire.read();
    #else
      return Wire.receive();
    #endif
  }
  
  
  void PinDriver::_write8(uint8_t addr, uint8_t d)
  {
    Wire.beginTransmission(_ic2_address);
    #if ARDUINO >= 100
      Wire.write(addr);
      Wire.write(d);
    #else
      Wire.send(addr);
      Wire.send(d);
    #endif
    Wire.endTransmission();
  }
  
}
