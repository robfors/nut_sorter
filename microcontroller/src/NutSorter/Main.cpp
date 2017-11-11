#include "NutSorter.h"


namespace NutSorter
{
  
  // here we declare all the system's concurrent tasks
  
  // all the angle offsets for every component can be adjusted here to
  //   account for any changes in hardware
  
  
  void Main::setup()
  {
    Hardware::setup();
    Carousel::setup();
    //if (!Ferromagnetic_measurement::setup())
    //{
      //Serial.println("ferromagnetic measurer setup error...");
      //Serial.println("|setup_error");
      //end();
    //}
    //if (!conductivity_measurement.setup())
    //{
    //  Serial.println("conductivity measurer setup error...");
    //  Serial.println("|setup_error");
    //  end();
    //}
  }
  
  
  void Main::start()
  {
    Carousel::start();
  }
  
  
  void Main::tick()
  {
    Hardware::tick();
    Initializer::tick();
    FerromagneticMeasurement::tick();
    ConductivityMeasurement::tick();
    ForceMeasurement::tick();
    ProfileMeasurement::tick();
    Interpreter::tick();
  }
  
}
