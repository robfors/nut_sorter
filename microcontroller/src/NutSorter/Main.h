#ifndef _NUT_SORTER_MAIN_H_
#define _NUT_SORTER_MAIN_H_

// parent for all the machine's functionality
// keeps the main file clean


namespace NutSorter
{
  
  class Main
  {
    
    public:
    
    // here we declare all the system's concurrent tasks
  
    // all the angle offsets for every component can be adjusted here to
    //   account for any changes in hardware
    
    static void setup();
    static void start();
    static void tick();
    
  };
  
}

#endif
