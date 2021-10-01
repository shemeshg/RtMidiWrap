#pragma once
#include "src/RtMidiWrap/midievent.h"


namespace Webchannel {
enum LOG_TO{
    CLIENT,
    SERVER
};

class EmitCommand{
public:     
     virtual void msgSend(RtMidiWrap::MidiEvent &m, LOG_TO logto, std::string userdata)=0;
    virtual void propegateClock(int portNumber, double barPosition, double spp, double barPositionNoReset, double sppNoReset) = 0;
};


}


