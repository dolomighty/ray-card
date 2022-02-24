
#include <XYZ.h>  // HEADER
#include <sfere.h>
#include <stdlib.h>

#define RND (rand()*1.0/RAND_MAX) 


XYZ light;  // HEADER




void db_init()  // HEADER
{

  SFERA sf={0};

  sf.raggio=10;
  sf.centro=XYZ(0,0,-sf.raggio);
  sfere.push_back(sf);

  for( int i=1 ; i<=3 ; i++ ){
    sf.raggio=1+RND*5;
    sf.centro=XYZ(i*20, 0,-sf.raggio);
    sf.vspd = -(1+RND);
    sfere.push_back(sf);

    sf.raggio=1+RND*5;
    sf.centro=XYZ(i*20,20,-sf.raggio);
    sf.vspd = -(1+RND);
    sfere.push_back(sf);

    sf.raggio=1+RND*5;
    sf.centro=XYZ(i*20,40,-sf.raggio);
    sf.vspd = -(1+RND);
    sfere.push_back(sf);
  }
}



