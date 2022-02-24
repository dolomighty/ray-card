
#ifndef _XYZ_h_
#define _XYZ_h_


#include <math.h>

struct XYZ{
  float x,y,z;
  XYZ(){}
  XYZ(float a,float b,float c){x=a;y=b;z=c;}
  XYZ operator+(XYZ r){return XYZ(x+r.x,y+r.y,z+r.z);}
//  XYZ operator·(XYZ r){return XYZ(x*r.x,y*r.y,z*r.z);}  // component-wise scalar
  XYZ operator*(float r){return XYZ(x*r,y*r,z*r);}  // scalar
  float operator%(XYZ r){return x*r.x+y*r.y+z*r.z;} // dot
  XYZ operator^(XYZ r){return XYZ(y*r.z-z*r.y,z*r.x-x*r.z,x*r.y-y*r.x);}  // cross
#define T (*this)
  XYZ operator!(){return T*(1/sqrt(T%T));}  // norm
#undef T
};


#endif


