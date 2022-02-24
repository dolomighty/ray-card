
#include "XYZ.cpp"


int G[]={247570,280596,280600,249748,18578,18577,231184,16,16};   // len 9

#define COUNT(A) (sizeof(A)/sizeof(A[0]))

#include "rand31dc.cc"

// uniform rand [0,1)
//#define RN (rand()*1./RAND_MAX)
//#define RN (0.5)
//#define RN rnd.ranf()

// quasi-gaussian rand [-1,+1)
#define RN ((rnd.ranf()+rnd.ranf()+rnd.ranf()+rnd.ranf()-2)/8)


float secs;
float raggio_sfere;

int ball_test_count;

int T( XYZ o , XYZ d , float&t , XYZ&n ){
  // ritorna materiale, distanza collisione e normale
  t=1e9;

  int m=0;    // m=0=sky
  float p=-o.z/d.z;
  if(.01<p)t=p,n=XYZ(0,0,1),m=1;  // m=1=plane (infatti normale ↑ z+ )

  for(int k=19;k--;){
    for(int j=COUNT(G);j--;){

      if(!(G[j]&1<<k))continue; // c'è una palla qui?

//      XYZ p=XYZ(k,0,j+4)-o; // vettore o→ball pos, solo che XYZ-XYZ non è definito
      // quindi si nega la pos e si somma. si ottiene il vettore ball pos→o,
      // ma basta organizzare i calcoli successivi per usare dot negativi e quant'altro
      XYZ p=o+XYZ(-k,0,-(j+4)); // ball pos
      
      float b=p%d;
      // se d·p > 0, vuol dire che la palla è dietro d (sarebbe davanti, ma p è negato, vedi sopra)
      // quindi è inutile proseguire, non può esserci intersezione valida con la o+d
      // è più veloce questo check che trovare t e rendersi conto che è negativo
      if(b>0)continue;

      float c=p%p-raggio_sfere;
      float q=b*b-c;
      if(q<0) continue;

      float s=-b-sqrt(q);
      if(s<t&&s>.01)t=s,n=!(p+d*t),m=2; // m=2=ball

//      ball_test_count ++;
    }
  }

  return m;
}


XYZ S( XYZ o , XYZ d , rand31dc &rnd ){
  // ritorna rgb del raggio
  float t;
  XYZ n;
  int m=T(o,d,t,n);
  if(!m)return XYZ(.7,.6,1)*pow(1-d.z,4);   // sky gradient
  XYZ h=o+d*t;
  XYZ l=!(XYZ(10+RN+10*sin(secs),10+RN+10*cos(secs),20+RN)+h*-1); // light pos
  XYZ r=d+n*(n%d*-2);
  float b=l%n;
  if(b<0||T(h,l,t,n))b=0;
  float p=pow(l%r*(b>0),100);  // metal shine
  if(m&1){
    h=h*.2; // densità scacchiera
    return((int)(ceil(h.x)+ceil(h.y))&1?XYZ(3,1,1):XYZ(3,3,3))*(b*.2+.1);
  }
  return XYZ(p,p,p)+S(h,r,rnd)*.5; // metal specular color + diffuse color * reflectiveness
}




void frame(){

  static uint8_t rgb[H][W][3];

  secs = SDL_GetTicks()/1000.0;
  raggio_sfere = 1;//2+sin(secs);
  ball_test_count=0;

//  XYZ g=!XYZ(-8,-16,0);
//  XYZ a = !(XYZ(0,0,1)^g)*.005;
//  XYZ b = !(g^a)*.005;

//  XYZ a = XYZ(-1,0,0)*.005;
//  XYZ g = XYZ( 0,1,0);
//  XYZ b = XYZ( 0,0,1)*.005;

  XYZ a = XYZ( camera.x.x , camera.x.y , camera.x.z )* -.005;
  XYZ g = XYZ( camera.y.x , camera.y.y , camera.y.z );
  XYZ b = XYZ( camera.z.x , camera.z.y , camera.z.z )* +.005;

  XYZ c=(a+b)*-(W/2)+g;

#pragma omp parallel
  for( int y=H-1 ; y>=0 ; y-- ){
      rand31dc rnd;
      rnd.seedi(y+123);

#pragma omp for
    for( int x=W-1 ; x>=0 ; x-- ){
      XYZ p(30,30,30);

#define RAYS 4
      for(int r=RAYS;r--;){
        XYZ t=a*RN*22+b*RN*22;
        p=S(
//          XYZ(17+10*sin(secs),16+10*cos(secs),8)+t,  // camera pos

//          XYZ(0,0,10)+t,  // camera pos

          XYZ( camera.t.x , camera.t.y , camera.t.z )+t,  // camera pos

          !(t*-1+(a*(RN+x)+b*(RN+y)+c)*16),
          rnd
        )*(240.0/RAYS)+p;
      }

      rgb[y][x][0]=p.x>255?255:p.x;
      rgb[y][x][1]=p.y>255?255:p.y;
      rgb[y][x][2]=p.z>255?255:p.z;
    }
  }


  SDL_UpdateTexture( framebuffer , NULL, rgb, W*sizeof(rgb[0][0]));
  SDL_Point center = {0,0};
  SDL_RenderCopyEx( renderer, framebuffer , NULL , NULL , 0 , 
    &center , (SDL_RendererFlip)(SDL_FLIP_HORIZONTAL | SDL_FLIP_VERTICAL));
  SDL_RenderPresent( renderer );

//  printf("ball_test_count %d\n",ball_test_count);
}


