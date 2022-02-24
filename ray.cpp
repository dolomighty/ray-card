
#include "XYZ.h"    // HEADER
#include <normal_ray.h>
#include <shadow_ray.h>
#include "rnd.h"
#include "db_init.h"
#include "skybox.h"
#include "frame.h"


XYZ ray( XYZ o , XYZ d , unsigned int &seed )   // HEADER
{
  // ritorna rgb del raggio



  // settiamo l'intersezione più distante a cielo o pavimento
  // in pratica, il default se non ci sono intersezioni più vicine
  float t=1e6;  // max depth
  int m=M_SKY;
  XYZ n;  // per il cielo la normale non conta, quindi no init

  float p=-o.z/d.z;
  if(p>.01){
    t=p;
    n=XYZ(0,0,1); // normale ↑ z+
    m=M_PLANE;  
  }


  normal_ray(o,d,t,n,m);

  // se non abbiamo intersezioni con gli oggetti 
  // e il raggio punta al cielo, torniamo RGB del cielo
  if(m==M_SKY){
//    return XYZ(.6,.7,1)*pow(1-d.z,9);   // sky gradient
    return skybox(d);
  }

  // ora m potrebbe esser M_PLANE o M_BALL
  // calcoliamo i vettori di riflessione e lo shadow ray

  XYZ h=o+d*t;  // hit point
//  XYZ l=!(XYZ( 10-RN+20*sin(secs) , RN+20*cos(secs) , 30+RN )+h*-1); // light pos
//  XYZ l=!(XYZ( 10+20*sin(secs) , 20*cos(secs) , 30 )+h*-1); // light pos
  XYZ l = !light;

//  XYZ l=!(XYZ( 10+RN , 20+RN , 30+RN )+h*-1); // light pos
  XYZ r = d+n*(n%d*-2);
//  XYZ r = d+n*(n%d*-2) + XYZ(fast_gauss_rand(seed),fast_gauss_rand(seed),fast_gauss_rand(seed))*0.01; // reflect dir

  float b=l%n; // lambert
  if(b<0||shadow_ray(h,l))b=0; // clamp+shadow

  if(m==M_PLANE){
    h=h*.1; // densità scacchiera
    return((int)(ceil(h.x)+ceil(h.y))&1?XYZ(2,2,2):XYZ(2,0,0))*(b*.5+.1);  // diffuse+specular+ambient
  }

  float s = l%r;
  if(s<0) s=0;
  p=pow(s*(b>0),1000);

//  return XYZ(b,b,b);
//  return XYZ(p,p,p);
//  return ray(h,r,seed);
  XYZ refl_rgb = ray(h,r,seed)*0.5;
  XYZ diff_rgb = XYZ(1,0.5,0.1)*b;
  XYZ spec_rgb = XYZ(10,10,10)*p;
  return refl_rgb+spec_rgb;
}



