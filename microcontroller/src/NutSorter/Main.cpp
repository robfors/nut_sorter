#include "NutSorter/Main.h"


namespace NutSorter
{
  
  AdafruitMotorShield Main::motor_shield;
  AdafruitStepperMotor* Main::stepper_motor_driver = motor_shield.getStepper(200, 2);
  StepperMotor Main::stepper_motor(stepper_motor_driver, 200, StepperMotor::StepType::Microstep, false);
  
  // here we declare all the system's concurrent tasks
  
  // all the angle offsets for every component can be adjusted here to
  //   account for any changes in hardware
  
  Carousel Main::carousel(&stepper_motor, CoterminalAngle(66.5)); // this offset may need to be adjusted in different lighting condtions 
  Chute Main::chute;
  Initializer Main::initializer(&carousel, CoterminalAngle(360.0));
  FerromagneticMeasurement Main::ferromagnetic_measurement(&carousel, CoterminalAngle(123.0), CoterminalAngle(125.5));
  ConductivityMeasurement Main::conductivity_measurement(&carousel, CoterminalAngle(179.0), CoterminalAngle(196.5));
  ForceMeasurement Main::force_measurement(&carousel, CoterminalAngle(230.0), CoterminalAngle(266.5));
  ProfileMeasurement Main::profile_measurement(&carousel, CoterminalAngle(295.0), CoterminalAngle(298.5));
  Interpreter Main::interpreter(&carousel, &chute, CoterminalAngle(349.0));
  
  
  void Main::setup()
  {
    motor_shield.begin();
    carousel.setup();
    chute.setup();
    initializer.setup();
    if (!ferromagnetic_measurement.setup())
    {
      Serial.println("ferromagnetic measurer setup error...");
      Serial.println("|setup_error");
      end();
    }
    if (!conductivity_measurement.setup())
    {
      Serial.println("conductivity measurer setup error...");
      Serial.println("|setup_error");
      end();
    }
    force_measurement.setup();
    profile_measurement.setup();
    interpreter.setup();
  }
  
  
  void Main::start()
  {
    carousel.start();
  }
  
  
  void Main::tick()
  {
    stepper_motor.tick();
    initializer.tick();
    ferromagnetic_measurement.tick();
    conductivity_measurement.tick();
    force_measurement.tick();
    profile_measurement.tick();
    interpreter.tick();
  }
  
}
