
#include <stdlib.h>   // card > aek.ppm
#include <stdio.h>
#include <math.h>

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

I T(v o,v d,F&t,v&n){
  t=1e9;
  I m=0;
  F p=-o.z/d.z;
  if(.01<p)t=p,n=v(0,0,1),m=1;
  for(I k=19;k--;)
    for(I j=9;j--;)
      if(G[j]&1<<k){
        v p=o+v(-k,0,-j-4);
        F b=p%d,c=p%p-1,q=b*b-c;
        if(q>0){
          F s=-b-sqrt(q);
          if(s<t&&s>.01)t=s,n=!(p+d*t),m=2;
        }
      }
      RET m;
    }


v S(v o,v d){
  F t;v n;
  I m=T(o,d,t,n);
  if(!m)RET v(.7,.6,1)*pow(1-d.z,4);
  v h=o+d*t,l=!(v(9+RN,9+RN,16)+h*-1),r=d+n*(n%d*-2);
  F b=l%n;
  if(b<0||T(h,l,t,n))b=0;
  F p=pow(l%r*(b>0),99);
  if(m&1){
    h=h*.2;
    RET((I)(ceil(h.x)+ceil(h.y))&1?v(3,1,1):v(3,3,3))*(b*.2+.1);
  }
  RET v(p,p,p)+S(h,r)*.5;
}


#define W 320
#define H 240

static unsigned char rgb[H][W][3];


I main(){

  v g=!v(-6,-16,0); // view vector
  v a=!(v(0,0,1)^g)*.004;
  v b=!(g^a)*.004;
  v c=(a+b)*-(W/2)+g;

  for( I y=H ; y-- ; ){
#pragma omp parallel for
    for( I x=W-1 ; x>=0 ; x-- ){
      v p(13,13,13);

#define RAYS 1
      for(I r=RAYS;r--;){
        v t=a*(RN-.5)*99+b*(RN-.5)*99;
        p=S(v(17,16,8)+t,!(t*-1+(a*(RN+x)+b*(y+RN)+c)*16))*(240/RAYS)+p;
      }
      rgb[y][x][0]=p.x;
      rgb[y][x][1]=p.y;
      rgb[y][x][2]=p.z;
    }
  }

  printf("P6 %d %d 255 ",W,H);
  for(I y=H;y--;)
    for(I x=W;x--;)
      printf("%c%c%c",rgb[y][x][0],rgb[y][x][1],rgb[y][x][2]);
}


/*


c++ -fopenmp -o main card.cpp
time ./main > image.ppm 


*/


