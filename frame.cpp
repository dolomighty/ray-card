
#define OP operator
#define I int
#define F float
#define RET return

struct v{
  F x,y,z;
  v OP+(v r){RET v(x+r.x,y+r.y,z+r.z);}
  v OP*(F r){RET v(x*r,y*r,z*r);}
  F OP%(v r){RET x*r.x+y*r.y+z*r.z;}
  v(){}
  v OP^(v r){RET v(y*r.z-z*r.y,z*r.x-x*r.z,x*r.y-y*r.x);}
  v(F a,F b,F c){x=a;y=b;z=c;}
  v OP!(){RET*this*(1/sqrt(*this%*this));}  // normalizza il vettore
};

I G[]={247570,280596,280600,249748,18578,18577,231184,16,16};

//#define RN (rand()*1./RAND_MAX)
#define RN (0.5)

F secs;


I T(v o,v d,F&t,v&n){
  // ritorna il materiale
  t=1e9;
  I m=0;    // m=0=sky
  F p=-o.z/d.z;
  if(.01<p)t=p,n=v(0,0,1),m=1;  // light dir and intensity m=1=plane
  for(I k=19;k--;)
    for(I j=9;j--;)
      if(G[j]&1<<k){
        v p=o+v(-k,0,-j-4); // metal position
        F b=p%d,c=p%p-1,q=b*b-c;
        if(q>0){
          F s=-b-sqrt(q);
          if(s<t&&s>.01)t=s,n=!(p+d*t),m=2; // m=2=ball
        }
      }
      RET m;
    }


v S(v o,v d){
  // ritorna rgb del raggio
  F t;v n;
  I m=T(o,d,t,n);
  if(!m)RET v(.7,.6,1)*pow(1-d.z,4);   // sky gradient
  v h=o+d*t;
  v l=!(v(9+RN+10*sin(secs),9+RN+10*cos(secs),16+RN)+h*-1); // light pos
  v r=d+n*(n%d*-2);
  F b=l%n;
  if(b<0||T(h,l,t,n))b=0;
  F p=pow(l%r*(b>0),10);  // metal shine
  if(m&1){
    h=h*.2; // densità scacchiera
    RET((I)(ceil(h.x)+ceil(h.y))&1?v(3,1,1):v(3,3,3))*(b*.2+.1);
  }
  RET v(p,p,p)+S(h,r)*.5; // metal specular color + diffuse color * reflectiveness
}




void frame(){

  static uint8_t rgb[H][W][3];

  secs = SDL_GetTicks()/1000.0;

  v g=!v(-8,-16,0); // view vector
//  v g=!v( sin(t) , cos(t) ,0); // view vector
  v a=!(v(0,0,1)^g)*.005;
  v b=!(g^a)*.005;
  v c=(a+b)*-(H/2)+g;

  for( I y=H ; y-- ; ){
#pragma omp parallel for
    for( I x=W-1 ; x>=0 ; x-- ){
      v p(13,13,13);
#define RAYS 1
      for(I r=RAYS;r--;){
        v t=a*(RN-.5)*22+b*(RN-.5)*22;
        p=S(
//          v(17+10*sin(secs),16+10*cos(secs),8)+t,  // camera pos
          v(17,16,8)+t,  // camera pos
          !(t*-1+(a*(RN+x)+b*(y+RN)+c)*16)
        )*(240/RAYS)+p;
      }
      rgb[y][x][0]=p.x>255?255:p.x;
      rgb[y][x][1]=p.y>255?255:p.y;
      rgb[y][x][2]=p.z>255?255:p.z;
    }
  }


  SDL_UpdateTexture( framebuffer , NULL, rgb, W*sizeof(rgb[0][0]));
  SDL_Point center = {0,0};
  SDL_RenderCopyEx( renderer, framebuffer , NULL , NULL , 0 , &center , (SDL_RendererFlip)(SDL_FLIP_HORIZONTAL | SDL_FLIP_VERTICAL));
  SDL_RenderPresent( renderer );
}


