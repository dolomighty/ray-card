
#include <SDL.h>
#include <camera.h>
#include <unistd.h>   // HEADER
#include <stdlib.h>
#include <math.h>
#include "XYZ.h"
#include <frame.h>


float secs;
Uint32 ticks_now;
Uint32 ticks_pre;
int tonemap;  // HEADER
bool bokeh;





void loop()   // HEADER
{

  static char mouselook = 0;
  camera.identity();
  camera.translate(20,20,10);
  camera.rotate_z(-M_PI*5/6);

  static char key_fwd = 0;
  static char key_back = 0;
  static char key_left = 0;
  static char key_right = 0;
  static char key_up = 0;
  static char key_down = 0;

  secs=0;
  ticks_now=0;
  ticks_pre=0;
  tonemap=2;
  bokeh=false;


  while(1){

    ticks_pre = ticks_now;
    ticks_now = SDL_GetTicks();
    secs = ticks_now/1000.0;
    
    static Uint32 look_renorm_deadline = ticks_now+3000;
    if( look_renorm_deadline < ticks_now ){
      look_renorm_deadline = ticks_now+3000;
      camera.normalize();
//      printf( "camera.normalize()\n" );
    }


    SDL_Event event;
    while( SDL_PollEvent( &event )){
      switch( event.type ){
//        case SDL_KEYDOWN:
//          printf(
//            "Il tasto %s e' stato premuto(%d)!\n",
//            SDL_GetKeyName(event.key.keysym.sym));
//          break;
//        case SDL_KEYUP:
//          printf(
//            "Il tasto %s e' stato alzato!\n",
//            SDL_GetKeyName(event.key.keysym.sym));
//          break;
        case SDL_KEYDOWN:
          switch(event.key.keysym.sym){
            case SDLK_t: tonemap++; break;
          }
          // no break intenzionale
        case SDL_KEYUP:
          switch(event.key.keysym.sym){
            case SDLK_w: key_fwd   = event.key.state; break;
            case SDLK_s: key_back  = event.key.state; break;
            case SDLK_a: key_left  = event.key.state; break;
            case SDLK_d: key_right = event.key.state; break;
            case SDLK_e: key_up    = event.key.state; break;
            case SDLK_c: key_down  = event.key.state; break;
          }
          break;
        case SDL_MOUSEMOTION:
//          printf(
//            "Il Mouse e' stato mosso di %d,%d pos %d,%d\n", 
//             event.motion.xrel, event.motion.yrel,
//             event.motion.x , event.motion.y );
          if(!mouselook)break;
          // controlli pitchyaw incrementali
          camera.rotate_x( +event.motion.yrel*0.002 );
          camera.rotate_z( +event.motion.xrel*0.002 );
          break;
        case SDL_MOUSEBUTTONDOWN:
//          printf(
//            "Il pulsante %d del Mouse e' stato "
//            "premuto a(%d,%d)\n",
//            event.button.button, 
//            event.button.x, 
//            event.button.y );
          mouselook=1;
          SDL_SetRelativeMouseMode(SDL_TRUE);
          break;
        case SDL_MOUSEBUTTONUP:
//          printf(
//            "Il pulsante %d del Mouse e' stato "
//            "alzato a(%d,%d)\n",
//            event.button.button, 
//            event.button.x, 
//            event.button.y );
          mouselook=0;
          SDL_SetRelativeMouseMode(SDL_FALSE);
          break;
        case SDL_QUIT:
//          printf( "SDL_QUIT\n" );
          return;
      }
    }


    // rettifica camera
    // il metodo di navigazione non assicura che l'asse x sia orizzontale (no twist)
    // qui ricalcoliamo gli assi x e z (y è il view vector)
    // x = y x up
    // z = x x y
    XYZ y = XYZ(camera.y.x,camera.y.y,camera.y.z);
    XYZ x = !(y ^ XYZ(0,0,1));
    camera.x.x = x.x; camera.x.y = x.y; camera.x.z = x.z;
    XYZ z = x ^ y; // non serve normalizzare, x e y sono unitari e perpendicolari
    camera.z.x = z.x; camera.z.y = z.y; camera.z.z = z.z;


    float speed_scale = (ticks_now - ticks_pre)/100.0;

    char move_x = 0;
    if(key_right == SDL_PRESSED) move_x ++;
    if(key_left  == SDL_PRESSED) move_x --;

    char move_y = 0;
    if(key_fwd  == SDL_PRESSED) move_y ++;
    if(key_back == SDL_PRESSED) move_y --;

    char move_z = 0;
    if(key_up   == SDL_PRESSED) move_z ++;
    if(key_down == SDL_PRESSED) move_z --;

    if(move_x||move_y||move_z) 
      camera.translate(
        move_x*speed_scale,
        move_y*speed_scale,
        move_z*speed_scale
      );


//    printf("cam pos %f %f %f\n"
//      ,camera.row[0].col[3]
//      ,camera.row[1].col[3]
//      ,camera.row[2].col[3]);

    

    frame();
    usleep( 1000 );
  }
}    



