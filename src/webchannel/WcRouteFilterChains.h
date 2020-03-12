#ifndef WCROUTEFILTERCHAINS_H
#define WCROUTEFILTERCHAINS_H
#include "src/MidiRoute/midifilterchain.h"

namespace Webchannel {

class WcRouteFilterChains {
public:
    std::unique_ptr<MidiRoute::MidiFilterChain> routeFilterChains = std::unique_ptr<MidiRoute::MidiFilterChain>(new MidiRoute::MidiFilterChain());
};

}

#endif // WCROUTEFILTERCHAINS_H
