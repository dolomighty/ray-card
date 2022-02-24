

#include <SDL.h>
#include "fb-size.h"
#include <db_init.h>
#include <loop.h>
#include <img_init.h>
#include <macros.h>



SDL_Renderer *renderer;   // HEADER
SDL_Texture *framebuffer; // HEADER





int main( int argc , char *argv[] )   // HEADER
{ 
  SDL_Window *win = SDL_CreateWindow( argv[0] , SDL_WINDOWPOS_UNDEFINED , SDL_WINDOWPOS_UNDEFINED 
    , W*ZOOM , H*ZOOM
    , 0 );
//    , SDL_WINDOW_FULLSCREEN_DESKTOP );
  if(!win) FATAL("SDL_CreateWindow");

  renderer = SDL_CreateRenderer( win , -1 , 0 );
  if(!renderer) FATAL("SDL_CreateRenderer");

  framebuffer = SDL_CreateTexture( renderer, SDL_PIXELFORMAT_RGB24, SDL_TEXTUREACCESS_STREAMING, W, H );
  if(!framebuffer) FATAL("SDL_CreateTexture");


  img_init();
  db_init();
//  if(!init()){
//    fprintf(stderr,"!init\n");
//    exit(1);
//  }
  
  loop();
  SDL_DestroyRenderer( renderer );
  SDL_DestroyWindow( win );
  return 0 ;
}


/*

make run

*/

