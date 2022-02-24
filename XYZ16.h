
#ifndef _XYZ16_h_
#define _XYZ16_h_

#include <stdint.h>

struct XYZ16 {

  int16_t x,y,z;
  
  bool operator==( const struct XYZ16 &other ) const {
    return x==other.x && y==other.y && z==other.z;
  }
};



#include <functional> // hash

struct XYZ16_hash
{
  std::size_t operator()( const struct XYZ16 &k ) const
  {
#define H(V) std::hash<int>()((int)V)
    return H(H(H(k.x)^k.y)^k.z);
#undef H
  }
};



#endif // _XYZ16_h_



