

#include <fast_gauss_rand.h>  // HEADER
#include <stdint.h>           // HEADER



float dummy_rnd( uint32_t &seed )   // HEADER
{
  return 0;
}




float (*rnd)( unsigned int &seed );   // HEADER



#define RN rnd(seed)    // HEADER


