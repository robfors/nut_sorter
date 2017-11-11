#ifndef _NUT_SORTER_SLOT_H_
#define _NUT_SORTER_SLOT_H_

/* We use these objects to give the code base access to each slots start
 * and end angle at any point in time.
 * 
 * It also acts as a storage for measurment data.
 */


namespace NutSorter
{
  
  class Carousel;
  
  class Slot
  {
    
    public:
    
    boolean has_ferromagnetic_object;
    boolean has_conductive_object;
    boolean has_heavy_object;
    Profile profile;
    
    Slot(CoterminalAngle start_offset_angle, CoterminalAngle end_offset_angle);
    
    boolean is_over(CoterminalAngle angle);
    boolean is_over(CoterminalAngle start_angle, CoterminalAngle end_angle);
    int odometer();
    void reset_odometer();
    CoterminalAngle start_angle();
    CoterminalAngle end_angle();
    
    boolean operator==(const Slot* other_slot);
    
    private:
    
    static const int _revolution_radius = 85; // mm
    static const int _revolution_circumference = _revolution_radius * M_PI; // mm
    
    CoterminalAngle _end_offset_angle;
    CoterminalAngle _odometer_start_angle;
    CoterminalAngle _start_offset_angle;
    
  };
  
}

#endif
