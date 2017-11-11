#include "NutSorter.h"


namespace NutSorter
{
  
  void Main::setup()
  {
    Hardware::Main::setup();
    Carousel::setup();
  }
  
  
  void Main::start()
  {
    Carousel::start();
  }
  
  
  void Main::tick()
  {
    Hardware::Main::tick();
    ConductivityMeasurement::tick();
    FerromagneticMeasurement::tick();
    ForceMeasurement::tick();
    Initializer::tick();
    Interpreter::tick();    
    ProfileMeasurement::tick();
  }
  
}
