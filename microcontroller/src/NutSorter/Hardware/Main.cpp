#include "Hardware.h"


namespace NutSorter
{
  namespace Hardware 
  {
    
    AdafruitMotorShield::Shield Main::motor_shield = AdafruitMotorShield::Shield();
    StepperMotor Main::carousel_stepper_motor = StepperMotor(motor_shield.get_stepper_motor(2), 200, StepperMotor::StepType::Microstep, false);
    ServoMotor Main::chute_servo_motor = ServoMotor(9, CoterminalAngle(90.0));
    LightSensor Main::carousel_calibrator_light_sensor = LightSensor(A1, 500);
    LightSensor Main::profile_light_sensor = LightSensor(A2, 200);
    ConductivitySensor Main::conductivity_sensor = ConductivitySensor((int[]){5, 6, 7}, 3);
    FerromagneticSensor Main::ferromagnetic_sensor = FerromagneticSensor();
    ForceSensor Main::force_sensor = ForceSensor(0);
    
    
    void Main::setup()
    {
      motor_shield.begin();
      chute_servo_motor.setup();
      carousel_calibrator_light_sensor.setup();
      profile_light_sensor.setup();
      if (!conductivity_sensor.setup())
      {
        Serial.println("conductivity sensor setup error...");
        Serial.println("|setup_error");
        end();
      }
      if (!ferromagnetic_sensor.setup())
      {
        Serial.println("ferromagnetic sensor setup error...");
        Serial.println("|setup_error");
        end();
      }
      force_sensor.setup();
    }
    
    
    void Main::tick()
    {
      carousel_stepper_motor.tick();
      conductivity_sensor.tick();
      ferromagnetic_sensor.tick();
    }
    
  }
}
  
