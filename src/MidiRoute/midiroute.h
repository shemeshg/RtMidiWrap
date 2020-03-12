#ifndef MIDIROUTE_H
#define MIDIROUTE_H
#include "src/RtMidiWrap/playmidiin.h"
#include "src/RtMidiWrap/playmidiout.h"
#include "midifilterchain.h"


namespace MidiRoute {
void doRoute(std::string configFile);






class MidiInRouter:public RtMidiWrap::PlayMidiIn{

    // protected temporary container for 14bit msb until lsb arrive
    std::map<int,int> msbForCc14Bit;
public:


    std::unique_ptr<MidiFilterChain> routeFilterChains;
    std::vector<int> cc14Bit {};
    std::vector<std::unique_ptr<RtMidiWrap::MidiEvent>> defferedMidiEvents;

    MidiInRouter(){
        routeFilterChains = std::unique_ptr<MidiFilterChain>(new MidiFilterChain());
    }

    void addCc14Bit(int channel,int cc){
        cc14Bit.push_back(channel * 1000 + cc);
    }

    void clearCc14Bit(){
        cc14Bit.clear();
    }
    void listener(RtMidiWrap::MidiEvent &m);

};




}





#endif // MIDIROUTE_H
