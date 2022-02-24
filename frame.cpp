
#include "XYZ.cpp"


#define COUNT(A) (sizeof(A)/sizeof(A[0]))


#include "fast_gauss_rand.cc"

float (*rnd)( unsigned int &seed );

float dummy_rnd( unsigned int &seed ){ return 0; }

#define RN rnd(seed)


float secs;
float raggio_sfere;

//int ball_test_count;

#define M_SKY   0
#define M_PLANE 1
#define M_BALL  2

int nearest_hit( XYZ o , XYZ d , float& t , XYZ& n ){
  // ritorna materiale, distanza collisione e normale
  t=1e9;

  int m=M_SKY;
  float p=-o.z/d.z;
  if(p>.01)t=p,n=XYZ(0,0,1),m=M_PLANE;  // normale ↑ z+

  // mettiamo una palla che rimbalza
  do{
    const float raggio=2;
//    XYZ p=o+XYZ(0,-10,-(raggio+10*abs(sin(secs*1))));
    float h = fmod(secs+0.2,2)-1; // [-1,+1]
    h = 1-h*h; // [0,1]
    XYZ p=o+XYZ(0,-10,-(raggio+10*h));
    float b=p%d;
    if(b>0)break;
    float c=p%p-raggio*raggio;
    float q=b*b-c;
    if(q<0)break;
    float s=-b-sqrt(q);
    if(s<t&&s>.01)t=s,n=!(p+d*t),m=M_BALL; 
  }while(0);

  do{
    const float raggio=2;
//    XYZ p=o+XYZ(0,-10,-(raggio+10*abs(sin(secs*1))));
    float h = fmod(secs+0.4,2)-1; // [-1,+1]
    h = 1-h*h; // [0,1]
    XYZ p=o+XYZ(10,-10,-(raggio+10*h));
    float b=p%d;
    if(b>0)break;
    float c=p%p-raggio*raggio;
    float q=b*b-c;
    if(q<0)break;
    float s=-b-sqrt(q);
    if(s<t&&s>.01)t=s,n=!(p+d*t),m=M_BALL; 
  }while(0);

  do{
    const float raggio=2;
//    XYZ p=o+XYZ(0,-10,-(raggio+10*abs(sin(secs*1))));
    float h = fmod(secs*1.3+0.6,2)-1; // [-1,+1]
    h = 1-h*h; // [0,1]
    XYZ p=o+XYZ(10,0,-(raggio+10*h));
    float b=p%d;
    if(b>0)break;
    float c=p%p-raggio*raggio;
    float q=b*b-c;
    if(q<0)break;
    float s=-b-sqrt(q);
    if(s<t&&s>.01)t=s,n=!(p+d*t),m=M_BALL; 
  }while(0);

  do{
    const float raggio=2;
//    XYZ p=o+XYZ(0,-10,-(raggio+10*abs(sin(secs*1))));
    float h = fmod(secs*1.3+0.6,2)-1; // [-1,+1]
    h = 1-h*h; // [0,1]
    XYZ p=o+XYZ(10,10,-raggio);
    float b=p%d;
    if(b>0)break;
    float c=p%p-raggio*raggio;
    float q=b*b-c;
    if(q<0)break;
    float s=-b-sqrt(q);
    if(s<t&&s>.01)t=s,n=!(p+d*t),m=M_BALL; 
  }while(0);

  return m;
}


#include "ray.cpp"


void frame(){

  static uint8_t rgb[H][W][3];

  secs = SDL_GetTicks()/1000.0;
  raggio_sfere = 1;//2+sin(secs);
//  ball_test_count=0;

  XYZ a = XYZ( camera.x.x , camera.x.y , camera.x.z )* +.005; // right vector
  XYZ g = XYZ( camera.y.x , camera.y.y , camera.y.z );        // view vector
  XYZ b = XYZ( camera.z.x , camera.z.y , camera.z.z )* -.005; // up vector

  XYZ c=(a+b)*-(W/2)+g;

  rnd = fast_gauss_rand;
  if(rays==1) rnd = dummy_rnd;

  for( int y=0 ; y<H ; y++ ){
#pragma omp parallel for
    for( int x=0 ; x<W ; x++ ){

      // una semplice hash di x e y per inizializzare il prng
      unsigned int seed = x*15485863^y*49979693;  

      XYZ p(0,0,0);

      for(int r=rays;r--;){
        XYZ t=a*RN*22+b*RN*22;
        p=ray(
          XYZ( camera.t.x , camera.t.y , camera.t.z )+t,  // camera pos
          !(t*-1+(a*(RN+x)+b*(RN+y)+c)*16),   // dir perturbata per bokeh
          seed
        )+p;
      }

      p.x /= rays;
      p.y /= rays;
      p.z /= rays;

//      // gamma 1.0
//      rgb[y][x][0]=255*p.x;
//      rgb[y][x][1]=255*p.y;
//      rgb[y][x][2]=255*p.z;

      // reinhart      
      rgb[y][x][0]=255*p.x/(p.x+0.3);
      rgb[y][x][1]=255*p.y/(p.y+0.3);
      rgb[y][x][2]=255*p.z/(p.z+0.3);

//      // gamma 2.2
//      rgb[y][x][0]=255*pow(p.x,1/2.2);
//      rgb[y][x][1]=255*pow(p.y,1/2.2);
//      rgb[y][x][2]=255*pow(p.z,1/2.2);
    }
  }


  SDL_UpdateTexture( framebuffer , NULL, rgb, W*sizeof(rgb[0][0]));
  SDL_RenderCopy( renderer, framebuffer , NULL , NULL );
  SDL_RenderPresent( renderer );
}


