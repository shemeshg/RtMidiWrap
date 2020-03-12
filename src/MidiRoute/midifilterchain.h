
#ifndef MIDIFILTERCHAIN_H
#define MIDIFILTERCHAIN_H

#include "make_unique.h"
#include "RoutFiltersChainClass.h"


namespace MidiRoute {



class MidiFilterChain
{
public:
    std::vector<std::unique_ptr<RoutFiltersChainClass>> chains;

    MidiFilterChain(){
    };
    int addChain(){
        chains.push_back(std::make_unique<RoutFiltersChainClass>());
        return chains.size() -1;
    }


};

}
#endif // MIDIFILTERCHAIN_H
