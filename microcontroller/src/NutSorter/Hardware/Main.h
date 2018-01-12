#ifndef _NUT_SORTER_HARDWARE_MAIN_H_
#define _NUT_SORTER_HARDWARE_MAIN_H_


namespace NutSorter
{
  namespace Hardware 
  {
    
    class Main
    {
      
      public:
      
      static AdafruitMotorShield::Shield motor_shield;
      static StepperMotor carousel_stepper_motor;
      static ServoMotor chute_servo_motor;
      static LightSensor carousel_calibrator_light_sensor;
      static ConductivitySensor conductivity_sensor;
      static FerromagneticSensor ferromagnetic_sensor;
      static ForceSensor force_sensor;
      static LightSensor profile_light_sensor;
      
      static void setup();
      static void tick();
      
    };
    
  }
}

#endif
