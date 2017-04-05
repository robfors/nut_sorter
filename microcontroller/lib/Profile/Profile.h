#ifndef _PROFILE_H_
#define _PROFILE_H_

/* This class saves an array of sample from a light sensor.
 * Right now all it does is give us an average sample.
 * 
 * Ideally it was going return the length of solid and air gaps of objects
 * so we could figure out exactly what kind of object it is, however
 * the samples were not reliable enough to use these methods.
 */ 

#include <Arduino.h>


class Profile
{
  
  public:
  
  Profile();
  
  void add_sample(unsigned int distance, unsigned int sample);
  unsigned int average_sample();
  void clear();
  //unsigned int length_of_first_air_gap();
  //unsigned int length_of_first_solid_gap();
  
  private:
  
  static const unsigned int _max_size = 50;
  
  unsigned int _last_sample_index;
  unsigned int _sample[_max_size];
  
};

#endif
