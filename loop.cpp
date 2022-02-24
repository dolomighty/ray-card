
#include "M34.hpp"

M34 camera;

#include "frame.cpp"



void loop(){

  static char mouselook = 0;
  camera.identity();
  camera.translate(20,20,10);
  camera.rotate_z(-M_PI*5/6);

  static char key_fwd = 0;
  static char key_back = 0;
  static char key_left = 0;
  static char key_right = 0;

  while(1){

    static Uint32 ticks_now = 0;
    static Uint32 ticks_pre = 0;
    ticks_pre = ticks_now;

    ticks_now = SDL_GetTicks();
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
        case SDL_KEYUP:
          switch(event.key.keysym.sym){
            case SDLK_w: key_fwd   = event.key.state; break;
            case SDLK_s: key_back  = event.key.state; break;
            case SDLK_a: key_left  = event.key.state; break;
            case SDLK_d: key_right = event.key.state; break;
          }
          break;
        case SDL_MOUSEMOTION:
//          printf(
//            "Il Mouse e' stato mosso di %d,%d pos %d,%d\n", 
//             event.motion.xrel, event.motion.yrel,
//             event.motion.x , event.motion.y );
          if(!mouselook)break;
          // controlli pitchyaw incrementali
          camera.rotate_x( +event.motion.yrel*0.001 );
          camera.rotate_z( +event.motion.xrel*0.001 );
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

    float speed_scale = (ticks_now - ticks_pre)/100.0;

    char move_y = 0;
    if(key_fwd  == SDL_PRESSED) move_y ++;
    if(key_back == SDL_PRESSED) move_y --;
    if(move_y) camera.translate(0,move_y*speed_scale,0);

    char move_x = 0;
    if(key_right == SDL_PRESSED) move_x ++;
    if(key_left  == SDL_PRESSED) move_x --;
    if(move_x) camera.translate(move_x*speed_scale,0,0);

//    printf("cam pos %f %f %f\n"
//      ,camera.row[0].col[3]
//      ,camera.row[1].col[3]
//      ,camera.row[2].col[3]);

    

    frame();
    usleep( 1000 );
  }
}    

