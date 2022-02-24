#include <stdlib.h>   // card > aek.ppm
#include <stdio.h>
#include <math.h>
#define OP operator
#define I int
#define F float
#define RET return
struct v{
F x,y,z;v OP+(v r){RET v(x+r.x
,y+r.y,z+r.z);}v OP*(F r){RET
v(x*r,y*r,z*r);}F OP%(v r){RET
x*r.x+y*r.y+z*r.z;}v(){}v OP^(v r
){RET v(y*r.z-z*r.y,z*r.x-x*r.z,x*r.
y-y*r.x);}v(F a,F b,F c){x=a;y=b;z=c;}v
OP!(){RET*this*(1/sqrt(*this%*
this));}};I G[]={247570,280596,280600,
249748,18578,18577,231184,16,16};
#define RN (rand()*1./RAND_MAX)
I T(v o,v d,F
&t,v&n){t=1e9;I m=0;F p=-o.z/d.z;if(.01
<p)t=p,n=v(0,0,1),m=1;for(I k=19;k--;)
for(I j=9;j--;)if(G[j]&1<<k){v p=o+v(-k
,0,-j-4);F b=p%d,c=p%p-1,q=b*b-c;if(q>0
){F s=-b-sqrt(q);if(s<t&&s>.01)t=s,n=!(
p+d*t),m=2;}}RET m;}v S(v o,v d){F t
;v n;I m=T(o,d,t,n);if(!m)RET v(.7,
.6,1)*pow(1-d.z,4);v h=o+d*t,l=!(v(9+RN
  ,9+RN,16)+h*-1),r=d+n*(n%d*-2);F b=l%
n;if(b<0||T(h,l,t,n))b=0;F p=pow(l%r*(b
>0),99);if(m&1){h=h*.2;RET((I)(ceil(
h.x)+ceil(h.y))&1?v(3,1,1):v(3,3,3))*(b
*.2+.1);}RET v(p,p,p)+S(h,r)*.5;}I
main(){printf("P6 512 512 255 ");v g=!v
(-6,-16,0),a=!(v(0,0,1)^g)*.002,b=!(g^a
)*.002,c=(a+b)*-256+g;for(I y=512;y--;)
for(I x=512;x--;){v p(13,13,13);for(I r
=10;r--;){v t=a*(RN-.5)*99+b*(RN-.5)*
99;p=S(v(17,16,8)+t,!(t*-1+(a*(RN+x)+b
*(y+RN)+c)*16))*24+p;}printf("%c%c%c"
,(I)p.x,(I)p.y,(I)p.z);}}


