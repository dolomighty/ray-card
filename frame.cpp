



#include "XYZ.h"
#include "camera.h"
#include <SDL.h>
#include <main.h>
#include "rnd.h"
#include "ray.h"
#include "sfere.h"
#include "db_update.h"
#include "fb-size.h"
#include "normal_ray.h"
#include "loop.h"



float distance_query( XYZ o , XYZ d )
{
  // settiamo l'intersezione più distante a cielo o pavimento
  // in pratica, il default se non ci sono intersezioni più vicine
  float t=1e6;  // max depth
  // non ci interessano in realtà
  int m;  
  XYZ n;

  float p = -o.z/d.z;
  if(p>.01) t=p;

  normal_ray(o,d,t,n,m);

  return t;
}






void frame()  // HEADER
{

  static float rgb[H][W][3];  // framebuffer
  static uint8_t rgb8[H][W][3];  // framebuffer

  XYZ a = XYZ( camera.x.x , camera.x.y , camera.x.z )* +.005; // right vector
  XYZ g = XYZ( camera.y.x , camera.y.y , camera.y.z );        // view vector
  XYZ b = XYZ( camera.z.x , camera.z.y , camera.z.z )* -.005; // up vector

  rnd = fast_gauss_rand;


  db_update();


  // implementiamo il depth of field dinamico
  // primo, valutiamo la distanza dal centro ottico
  // poi a usiamo nei calcoli del bokeh
  static float dist=1;
  float dist_tgt = distance_query( XYZ( camera.t.x , camera.t.y , camera.t.z ), g );
  if(dist_tgt<1) dist_tgt=1;
  
//  // IIR 2nd order - non funz ben
//  float delta = dist_tgt-dist;
//  float dist_incr = delta*delta*(ticks_now-ticks_pre)/1000.0;
//  if(delta>0){
//    if(dist_incr>delta)dist_incr=delta;
//  }else{
//    if(dist_incr<delta)dist_incr=delta;
//  }
//  dist=dist+dist_incr;

  dist=dist_tgt;
//  printf("dist %f\n",dist);


  // accumula in un framebuffer float
  // la scena, un raggio per pixel con bokeh
  // il framebuffer viene 

  static unsigned int seed=1;

  for( int y=0 ; y<H ; y++ ){
#pragma omp parallel for
    for( int x=0 ; x<W ; x++ ){

      XYZ t = a*RN*100 + b*RN*100;  // perturbazione per bokeh
      XYZ p = ray(
        XYZ( camera.t.x , camera.t.y , camera.t.z )+t,  // origine + perturbazione
        !(t*-1+(a*(RN+x-W/2)+b*(RN+y-H/2)+g)*dist),   // dir - perturbazione
        seed
      );
      // grazie al -/+ perturbazione esisterà un piano frontale 
      // che sarà a fuoco, dove i raggi perturbati 
      // del singolo pixel in media convergono

      // accumulo sotto filtro LP IIR
      rgb[y][x][0] = rgb[y][x][0] + (p.x-rgb[y][x][0])*0.1;
      rgb[y][x][1] = rgb[y][x][1] + (p.y-rgb[y][x][1])*0.1;
      rgb[y][x][2] = rgb[y][x][2] + (p.z-rgb[y][x][2])*0.1;

      p.x = rgb[y][x][0];
      p.y = rgb[y][x][1];
      p.z = rgb[y][x][2];

      switch(tonemap){
        default:
          tonemap=1;
          // no break intenzionale
        case 1:// gamma 1.0
          // clamp
          if(p.x<0) p.x=0; else if(p.x>1) p.x=1;
          if(p.y<0) p.y=0; else if(p.y>1) p.y=1;
          if(p.z<0) p.z=0; else if(p.z>1) p.z=1;
          rgb8[y][x][0]=255*p.x;
          rgb8[y][x][1]=255*p.y;
          rgb8[y][x][2]=255*p.z;
          break;
        case 2:// gamma 2.2
          // clamp
          if(p.x<0) p.x=0; else if(p.x>1) p.x=1;
          if(p.y<0) p.y=0; else if(p.y>1) p.y=1;
          if(p.z<0) p.z=0; else if(p.z>1) p.z=1;
          rgb8[y][x][0]=255*pow(p.x,1/2.2);
          rgb8[y][x][1]=255*pow(p.y,1/2.2);
          rgb8[y][x][2]=255*pow(p.z,1/2.2);
          break;
        case 3:// reinhart
          // non necessita di clamp, è una tecnica hdr
          rgb8[y][x][0]=255*p.x/(p.x+0.2);
          rgb8[y][x][1]=255*p.y/(p.y+0.2);
          rgb8[y][x][2]=255*p.z/(p.z+0.2);
          break;
//        case 4:// gamma 2.2 via sparse lut - più lento del gamma via pow
//          rgb8[y][x][0]=range_find(p.x,gamma_2p2,COUNT(gamma_2p2));
//          rgb8[y][x][1]=range_find(p.y,gamma_2p2,COUNT(gamma_2p2));
//          rgb8[y][x][2]=range_find(p.z,gamma_2p2,COUNT(gamma_2p2));
//          break;
      }


    }
  }

  SDL_UpdateTexture( framebuffer , NULL, rgb8, W*sizeof(rgb8[0][0]));
  SDL_RenderCopy( renderer, framebuffer , NULL , NULL );
  SDL_RenderPresent( renderer );
}
