#ifndef SONGPOSITION_H
#define SONGPOSITION_H
//#include <string>
//#include <iostream>
#include<cmath>
//#include "RtMidiWrap.h"
#include "common.h"

namespace RtMidiWrap {
class SongPosition {
public:

    double timeSig = 4;
    double timeSigDivBy = 4;
    double fromSppPos = 0;

    double clock = 0;
    double spp = 0;
    double sppNoReset = 0;
    double getBarPosition(){

        double totalBars = timeSig * timeSigDivBy ;
        return ((spp - fromSppPos )/ totalBars) ;
    }

    double getBarPositionNoReset(){

        double totalBars = timeSig * timeSigDivBy ;
        return ((sppNoReset - fromSppPos )/ totalBars) ;
    }

    void tick(){
        clock++;
        spp = spp + (timeSigDivBy/4.0) * ((timeSig * timeSigDivBy)/timeSig )/24.0;
        sppNoReset = spp + (timeSigDivBy/4.0) * ((timeSig * timeSigDivBy)/timeSig )/24.0;
        int g= (int)clock;
        if (g %24 ==0){clock=0;}

        return;

    }
    void setSpp(std::vector< BYTE> &message){
        unsigned int nBytes = message.size();

        int sppTotal = 0;

        for ( unsigned int i=1; i<nBytes; i++ )
          sppTotal = sppTotal + ( (int)message.at(i) << ( 7 * (i -1) ) );
        int ipow = (int)(log2(timeSigDivBy) - 2);

        spp = sppTotal * ( pow (4, ipow));
    }

};
}
#endif // SONGPOSITION_H
