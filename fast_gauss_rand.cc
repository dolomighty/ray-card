
#include <assert.h>
#include <stdlib.h>


//float fast_gauss_rand( unsigned int &x ){
//
//  // https://en.wikipedia.org/wiki/Xorshift
//
//  assert(sizeof(int)>=4);
//
//  int r = 0;
//
//  x ^= x << 13;   x ^= x >> 17;   x ^= x << 5;    r += x&32767;
//  x ^= x << 13;   x ^= x >> 17;   x ^= x << 5;    r += x&32767;
//  x ^= x << 13;   x ^= x >> 17;   x ^= x << 5;    r += x&32767;
//  x ^= x << 13;   x ^= x >> 17;   x ^= x << 5;    r += x&32767;
//
//  // r = [0,32767*4]
//
//  return (r-32767*2)    // [-32767*2,+32767*2]
//      / (32767*4.0);    // [-0.5,+0.5]
//}




float fast_gauss_rand( unsigned int &seed ){

    // generiamo 4 random di bassa qualità (ma veloci)
    // ritorniamo la media, scalata a [-0.5,+0.5]
    
    assert(sizeof(int)>=4);

    int r = 0;

    seed = (214013*seed+2531011);   r += (seed>>14)&32767;
    seed = (214013*seed+2531011);   r += (seed>>14)&32767;
    seed = (214013*seed+2531011);   r += (seed>>14)&32767;
    seed = (214013*seed+2531011);   r += (seed>>14)&32767;

    // r = [0,32767*4]

    return (r-(32767*2))    // [-32767*2,+32767*2]
        / (32767*4.0);      // [-0.5,+0.5]
}



//float fast_gauss_rand( unsigned int &seed ){
//    return (
//      (rand()&32767)+
//      (rand()&32767)+
//      (rand()&32767)+
//      (rand()&32767)
//      -32767*2
//    )/(32767*4.0);
//}







//#include <stdio.h>
//int main( int argc , char * argv[] ){
//  unsigned int seed = 1;
//  float a=0;
//  for(int i=10000000;i--;){
//    a += fast_gauss_rand(seed);
//    a += fast_gauss_rand(seed);
//    a += fast_gauss_rand(seed);
//    a += fast_gauss_rand(seed);
//    a += fast_gauss_rand(seed);
//    a += fast_gauss_rand(seed);
//    a += fast_gauss_rand(seed);
//    a += fast_gauss_rand(seed);
//    a += fast_gauss_rand(seed);
//    a += fast_gauss_rand(seed);
//  }
//  printf("%f\n",a);
//  return 0;
//}


/*

c++ -O3 -o main fast_gauss_rand.cc && time ./main

*/

