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

#ifndef _ADAFRUIT_MOTTRSHIELD_PIN_DRIVER_H_
#define _ADAFRUIT_MOTTRSHIELD_PIN_DRIVER_H_


#define PCA9685_SUBADR1 0x2
#define PCA9685_SUBADR2 0x3
#define PCA9685_SUBADR3 0x4

#define PCA9685_MODE1 0x0
#define PCA9685_PRESCALE 0xFE

#define LED0_ON_L 0x6
#define LED0_ON_H 0x7
#define LED0_OFF_L 0x8
#define LED0_OFF_H 0x9

#define ALLLED_ON_L 0xFA
#define ALLLED_ON_H 0xFB
#define ALLLED_OFF_L 0xFC
#define ALLLED_OFF_H 0xFD


namespace AdafruitMotorShield
{
  
  class PinDriver
  {
    
    public:
    
    PinDriver(uint8_t addr = 0x40);
    void begin();
    void reset();
    void set_pwm_frequency(float frequency);
    void set_pin_duty_cycle(uint8_t pin, uint16_t val);
    void set_pin_state(uint8_t pin, boolean val);
    
    private:
    
    uint8_t _ic2_address;
    uint8_t _read8(uint8_t addr);
    void _write8(uint8_t addr, uint8_t d);
    
    void _set_pin_pwm_phases(uint8_t num, uint16_t phase_begin, uint16_t phase_end);
    
  };
  
}

#endif
