
#include <stdlib.h>
#include <SDL.h>
#include <unistd.h>


static SDL_Renderer *renderer;
static SDL_Texture *framebuffer;


#include "fb-size.h"
#include "loop.cpp"


int main( int argc , char *argv[] ){ 
  SDL_Window *win = SDL_CreateWindow( argv[0] , SDL_WINDOWPOS_UNDEFINED , SDL_WINDOWPOS_UNDEFINED , 1024 , 768 , 0 );
  if(!win){
    fprintf(stderr,"!win\n");
    exit(1);
  }
  renderer = SDL_CreateRenderer( win , -1 , 0 );
  if(!renderer){
    fprintf(stderr,"!renderer\n");
    exit(1);
  }
  framebuffer = SDL_CreateTexture( renderer, SDL_PIXELFORMAT_RGB24, SDL_TEXTUREACCESS_STREAMING, W, H );
  if(!framebuffer){
    fprintf(stderr,"!framebuffer\n");
    exit(1);
  }
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

