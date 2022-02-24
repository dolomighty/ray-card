

XYZ ray( XYZ o , XYZ d , unsigned int &seed ){
  // ritorna rgb del raggio
  float t;
  XYZ n;
  int m=nearest_hit(o,d,t,n);
  if(m==M_SKY)return XYZ(.6,.7,1)*pow(1-d.z,9);   // sky gradient
  XYZ h=o+d*t;  // hit point
//  XYZ l=!(XYZ( 10-RN+20*sin(secs) , RN+20*cos(secs) , 30+RN )+h*-1); // light pos
  XYZ l=!(XYZ( 10+RN , 20+RN , 30+RN )+h*-1); // light pos
  XYZ r=d+n*(n%d*-2); // reflect dir
  float b=l%n; // lambert
  if(b<0||nearest_hit(h,l,t,n))b=0; // clamp+shadow
  float p=pow(l%r*(b>0),10);  // shine

  if(m==M_PLANE){
    h=h*.2; // densità scacchiera
    return((int)(ceil(h.x)+ceil(h.y))&1?XYZ(3,3,3):XYZ(3,1,1))*(b*.1+.1);  // diffuse+specular+ambient
  }

//  return XYZ(b,b,b);
//  return XYZ(p,p,p);
//  return ray(h,r,seed);
  return XYZ(p,p,p)+ray(h,r,seed)*.2; // metal specular color + reflect color * reflectiveness
}



