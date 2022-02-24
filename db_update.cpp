

#include "XYZ.h"
#include "sfere.h"
#include "db_init.h"


extern float secs;



void db_update()  // HEADER
{

  light = XYZ( 10+20*sin(secs) , 20*cos(secs) , 30 );

  const float g = 0.03;

//  for( int i=1 ; i<sfere.size() ; i++ ){
//    // perche due volte l'incremento?
//    // se si esegue l'update della posizione prima della velocità
//    // gli arrotondamenti provocano incremento di energia
//    // quindi la palla rimbalza sempre più in alto
//    // se si esegue dopo, accade l'opposto.
//    // aggiornando prima e dopo, gli effetti si cancellano
//    // simile all'integrazione leapfrog, se non sbaglio
//    sfere[i].centro.z += sfere[i].vspd/2;
//    sfere[i].vspd += g;
//    sfere[i].centro.z += sfere[i].vspd/2;
//    if( sfere[i].centro.z < -sfere[i].raggio ) continue;
//    if( sfere[i].vspd < 0 )continue;
//    sfere[i].vspd = -sfere[i].vspd;
//  }


//  {
//    // puliamo la griglia
//    obs_from_cell_t::iterator cel;
//    for( cel = obs_from_cell.begin(); cel != obs_from_cell.end(); ++cel ){
//      cel->second.obs.clear();
//    }
//    obs_from_cell.clear();
//  }
//  // sembra esser sufficente pulire solo il contenitore (piuttosto che anche i contenuti)

//  obs_from_cell.clear();
//
//  // aggiorniamo la griglia voxelizzando approssimativamente gli oggetti
//  for( int i=0 ; i<sfere.size() ; i++ ){
//    vox_sphere(&sfere[i]);
//  }

//  {
//    // dump
////    printf("%ld\n",obs_from_cell.size());
//    obs_from_cell_t::iterator cel;
//    for( cel = obs_from_cell.begin(); cel != obs_from_cell.end(); ++cel ){
//      printf("%d;%d;%d:",cel->first.x,cel->first.y,cel->first.z);
//      std::unordered_set<struct SFERA *>::iterator ob;
////      printf("%ld ",cel->second.obs.size());
//      for( ob = cel->second.obs.begin(); ob != cel->second.obs.end(); ++ob ){
//        printf("%d ",(*ob)->index);
//      }
//      printf("\n");
//    }
//    exit(1);
//  }
  

}



