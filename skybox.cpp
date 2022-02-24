

#include "XYZ.h"    // HEADER
#include "img_init.h"




float linear_remap( float in , float in_min , float in_max , float out_min , float out_max )
{
  return (in-in_min)*(out_max-out_min)/(in_max-in_min)+out_min;
}


XYZ skybox( XYZ d )   // HEADER
{

  XYZ abs = { fabs(d.x) , fabs(d.y) , fabs(d.z) };

#define BPP 3

  if( abs.x >= abs.y && abs.x >= abs.z ){
    if(d.x>0){
      // dobbiamo calcolare l'intersezione sul piano
      // molti parametri sono fissi: o del raggio = 0, d del piano ±1
      // facendo i vari calcoli per via simbolica si arriva a y/x e z/x per il piano x=1
      // per gli altri piani ovviamente basta scambiare le coords
      // il range di {yz}/x = ±1
      int u = linear_remap( d.y/d.x , +1,-1 , skybox_surf->w*3/4,skybox_surf->w*4/4 );
      int v = linear_remap( d.z/d.x , +1,-1 , skybox_surf->h*1/3,skybox_surf->h*2/3 );
      uint8_t *p = (uint8_t*)skybox_surf->pixels + u*BPP + skybox_surf->pitch*v;
      return XYZ(p[0]/255.0,p[1]/255.0,p[2]/255.0);
    }else{
      int u = linear_remap( d.y/d.x , +1,-1 , skybox_surf->w*1/4,skybox_surf->w*2/4 );
      int v = linear_remap( d.z/d.x , -1,+1 , skybox_surf->h*1/3,skybox_surf->h*2/3 );
      uint8_t *p = (uint8_t*)skybox_surf->pixels + u*BPP + skybox_surf->pitch*v;
      return XYZ(p[0]/255.0,p[1]/255.0,p[2]/255.0);
    }
  }

  if( abs.y >= abs.x && abs.y >= abs.z ){
    if(d.y>0){
      int u = linear_remap( d.x/d.y , -1,+1 , skybox_surf->w*2/4,skybox_surf->w*3/4 );
      int v = linear_remap( d.z/d.y , +1,-1 , skybox_surf->h*1/3,skybox_surf->h*2/3 );
      uint8_t *p = (uint8_t*)skybox_surf->pixels + u*BPP + skybox_surf->pitch*v;
      return XYZ(p[0]/255.0,p[1]/255.0,p[2]/255.0);
    }else{
      int u = linear_remap( d.x/d.y , -1,+1 , skybox_surf->w*0/4,skybox_surf->w*1/4 );
      int v = linear_remap( d.z/d.y , -1,+1 , skybox_surf->h*1/3,skybox_surf->h*2/3 );
      uint8_t *p = (uint8_t*)skybox_surf->pixels + u*BPP + skybox_surf->pitch*v;
      return XYZ(p[0]/255.0,p[1]/255.0,p[2]/255.0);
    }
  }

  if( abs.z >= abs.x && abs.z >= abs.y ){
    if(d.z>0){
      int u = linear_remap( d.y/d.z , -1,+1 , skybox_surf->w*1/4,skybox_surf->w*2/4 );
      int v = linear_remap( d.x/d.z , +1,-1 , skybox_surf->h*0/3,skybox_surf->h*1/3 );
      uint8_t *p = (uint8_t*)skybox_surf->pixels + u*BPP + skybox_surf->pitch*v;
      return XYZ(p[0]/255.0,p[1]/255.0,p[2]/255.0);
    }else{
      int u = linear_remap( d.y/d.z , +1,-1 , skybox_surf->w*1/4,skybox_surf->w*2/4 );
      int v = linear_remap( d.x/d.z , +1,-1 , skybox_surf->h*2/3,skybox_surf->h*3/3 );
      uint8_t *p = (uint8_t*)skybox_surf->pixels + u*BPP + skybox_surf->pitch*v;
      return XYZ(p[0]/255.0,p[1]/255.0,p[2]/255.0);
    }
  }

  return XYZ(0,0,0);
}



