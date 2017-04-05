#include "Profile.h"


//
// public
//


Profile::Profile()
{
  clear();
}


void Profile::add_sample(unsigned int distance, unsigned int sample)
{
  // one limitation with the implementation is that the first sample in _sample[] will always end up being 0
  if (distance >= _max_size)
    return;
  if (distance <= _last_sample_index)
    return;
  
  unsigned int last_sample = _sample[_last_sample_index];
  _last_sample_index++;
  while (_last_sample_index != distance)
  {
    _sample[_last_sample_index] = last_sample;
    _last_sample_index++;
  }
  _sample[distance] = sample;
}


unsigned int Profile::average_sample()
{
  unsigned long average = 0;
  unsigned int num_samples = 0;
  for (unsigned int sample_index = 0; sample_index < _max_size; sample_index++)
  {
    unsigned int sample = _sample[sample_index];
    if (sample != 0)
    {
      average += sample;
      num_samples++;
    }
  }
  return average / num_samples;
}


void Profile::clear()
{
  for (unsigned int sample_index = 0; sample_index < _max_size; sample_index++)
  {
    _sample[sample_index] = 0;
  }
  _last_sample_index = 0;
}


/*unsigned int Profile::length_of_first_solid_gap()
{
  unsigned int index_of_first_solid_sample = 0;
  for (unsigned int sample_index = 0; sample_index < _max_size; sample_index++)
  {
    if (_sample[sample_index] == HIGH)
    {
      index_of_first_solid_sample = sample_index;
      break;
    }
  }
  
  unsigned int index_of_last_solid_sample = 0;
  for (unsigned int sample_index = index_of_first_solid_sample; sample_index < _max_size; sample_index++)
  {
    if (_sample[sample_index] == LOW)
    {
      break;
      index_of_last_solid_sample = sample_index - 1;
    }
  }
  
  return index_of_last_solid_sample - index_of_first_solid_sample;
}


unsigned int Profile::length_of_first_air_gap()
{
  unsigned int index_of_first_solid_sample = 0;
  for (unsigned int sample_index = 0; sample_index < _max_size; sample_index++)
  {
    if (_sample[sample_index] == HIGH)
    {
      index_of_first_solid_sample = sample_index;
      break;
    }
  }
  
  unsigned int index_of_first_air_sample = 0;
  for (unsigned int sample_index = index_of_first_solid_sample; sample_index < _max_size; sample_index++)
  {
    if (_sample[sample_index] == LOW)
    {
      break;
      index_of_first_air_sample = sample_index;
    }
  }
  
  unsigned int index_of_last_air_sample = 0;
  for (unsigned int sample_index = index_of_first_air_sample; sample_index < _max_size; sample_index++)
  {
    if (_sample[sample_index] == HIGH)
    {
      index_of_last_air_sample = sample_index - 1;
      break;
    }
  }
  
  return index_of_last_air_sample - index_of_first_air_sample;
}*/


//
// private
//
