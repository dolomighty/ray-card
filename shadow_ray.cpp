



#include "XYZ.h"    // HEADER
#include "sfere.h"    // HEADER



bool shadow_ray( XYZ ori , XYZ dir )    // HEADER
{
  // in questo caso, ci interessa solo sapere se ori è in ombra
  // altre info tipo chi la occlude o la normale di intersezione non servono
  // di conseguenza, è sufficente fermarsi alla prima occlusione
  for( int i=0 ; i<sfere.size() ; i++ ){
    XYZ p=ori+sfere[i].centro;
    float b=p%dir;
    if(b>0)continue;
    float c=p%p-sfere[i].raggio*sfere[i].raggio;
    float q=b*b-c;
    if(q<0)continue;
    return true;
  }
  return false;
}


