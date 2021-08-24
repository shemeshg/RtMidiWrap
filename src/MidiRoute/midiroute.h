#ifndef MIDIROUTE_H
#define MIDIROUTE_H
#include "src/RtMidiWrap/playmidiin.h"
#include "src/RtMidiWrap/playmidiout.h"
#include "midifilterchain.h"


namespace MidiRoute {
void doRoute(std::string configFile);




class NrpnContainer {
public:
    int nrpnCtrlMsb = -1;
    int nrpnCtrlLsb = -1;
    int nrpnDataMsb = -1;
    int nrpnDataLsb = -1;
};

class MidiInRouter:public RtMidiWrap::PlayMidiIn{
private:
    // protected temporary container for 14bit msb until lsb arrive
    // <channel+cc,data2>
    std::map<int,int> msbForCc14Bit;
    std::map<int,NrpnContainer> nrpnPack;

    void proccess14bitCc(RtMidiWrap::MidiEvent &m);
    void proccessNrpn(RtMidiWrap::MidiEvent &m);
    void proccessChainsAndFilters(RtMidiWrap::MidiEvent &m);

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
