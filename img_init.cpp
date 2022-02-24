

#include <SDL.h>  // HEADER

SDL_Surface *skybox_surf; // HEADER



#include <SDL_image.h>
#include <math.h>
#include <stdint.h>
#include <macros.h>



void linearRGB_from_sRGB_inplace( SDL_Surface *surf ){
  for( int h=0 ; h<surf->h ; h++ ){
#pragma omp parallel for
    for( int w=0 ; w<surf->w ; w++ ){
      uint8_t *p = (uint8_t*)surf->pixels + w*3 + surf->pitch*h;
      p[0] = 255*pow(p[0]/255.0,2.2);
      p[1] = 255*pow(p[1]/255.0,2.2);
      p[2] = 255*pow(p[2]/255.0,2.2);
    }
  }
}




void img_init()   // HEADER
{
  if(!IMG_Init(IMG_INIT_PNG|IMG_INIT_JPG)) FATAL("IMG_Init");
  skybox_surf = IMG_Load("i/skybox.jpg");
  if(!skybox_surf) FATAL("IMG_Load");
  linearRGB_from_sRGB_inplace(skybox_surf);
}

