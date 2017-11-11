#include "NutSorter.h"


namespace NutSorter
{
  
  class Hardware
  {
    
    public:
    
    static AdafruitMotorShield::Shield motor_shield;
    static StepperMotor carousel_stepper_motor;
    static Servo chute_servo;
    static LightSensor carousel_calibrator_light_sensor;
    static ConductivitySensor conductivity_sensor;
    static FerromagneticSensor ferromagnetic_sensor;
    static ForceSensor force_sensor;
    static LightSensor profile_light_sensor;
    
    static void setup();
    static void tick();
    
  };
  
}
