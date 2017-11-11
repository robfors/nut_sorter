#include "NutSorter.h"


namespace NutSorter
{
  
  AdafruitMotorShield::Shield Hardware::motor_shield = AdafruitMotorShield::Shield();
  StepperMotor Hardware::carousel_stepper_motor = StepperMotor(motor_shield.get_stepper_motor(2), 200, StepperMotor::StepType::Microstep, false);
  Servo Hardware::chute_servo = Servo(9, CoterminalAngle(90.0));
  LightSensor Hardware::carousel_calibrator_light_sensor = LightSensor(A1, 500);
  ConductivitySensor Hardware::conductivity_sensor = ConductivitySensor((int[]){5, 6, 7}, 3);
  FerromagneticSensor Hardware::ferromagnetic_sensor = FerromagneticSensor();
  ForceSensor Hardware::force_sensor = ForceSensor(0);
  LightSensor Hardware::profile_light_sensor = LightSensor(A2, 200);
  
  
  void Hardware::setup()
  {
    motor_shield.begin();
    chute_servo.setup();
    carousel_calibrator_light_sensor.setup();
  }
  
  
  void Hardware::tick()
  {
    carousel_stepper_motor.tick();
  }
  
}
