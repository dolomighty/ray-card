

// HEADERBEG
#define M_SKY   0
#define M_PLANE 1
#define M_BALL  2
// HEADEREND



#include "XYZ.h"
#include "sfere.h"


void normal_ray( XYZ o , XYZ d , float& t , XYZ& n , int &m )   // HEADER
{
  // aggiorna l'intersezione con la più vicina
  for( int i=0 ; i<sfere.size() ; i++ ){
    XYZ p=o+sfere[i].centro;
    float b=p%d;
    if(b>0)continue;
    float c=p%p-sfere[i].raggio*sfere[i].raggio;
    float q=b*b-c;
    if(q<0)continue;
    float s=-b-sqrt(q);
    if(s<t&&s>.01)t=s,n=!(p+d*t),m=M_BALL; 
  }
}




//// IMPL
//
//#include <vox_walk.h> // auto-hdr/vox_walk.h
//#include "CELL.h"
//
//
//
//bool on_voxel(
//  CELL cell, 
//  XYZ origin,
//  XYZ direction,
//  int &material,
//  XYZ &normal,
//  float &t
//){
//  // aggiorna le info di intersezione material/normal/t
//
//  // viene chiamata da vox_walk solo se il voxel contiene qualcosa
//  // return false; continua il cammino (passiamo quindi al prossimo voxel non vuoto lungo il raggio)
//  // return true; termina il cammino
//
//  // qui si interseca con gli oggetti
//  // cielo e piano sono last resort
//  // e son già considerati in ray()
//
//  for( auto it=cell.obs.begin(); it!=cell.obs.end() ; it++ ){
//    SFERA *sph = *it; // alias, per chiarezza ... tanto poi viene ottimizzato via
//
//    XYZ p = origin+sph->centro;
//    float b=p%direction;
//    if(b>0)continue;  // no intersect
//    float c=p%p-sph->raggio*sph->raggio;
//    float q=b*b-c;
//    if(q<0)continue;  // no intersect
//    float s=-b-sqrt(q);
//    if(s<t&&s>.01){
//      t=s;
//      normal=!(p+direction*t);
//      material=M_BALL;
//    }
//  }
//
//  return true;
//}
//// ENDIMPL
//
//
//
//
//void normal_ray( XYZ o , XYZ d , float& t , XYZ& n , int &m )
//// IMPL
//{
//  // ritorna materiale, distanza collisione e normale
//  // usa il partizionamento a voxel per sveltire le intersezioni
//  vox_walk( o , d , m , n , t , on_voxel );
//}
//// ENDIMPL

