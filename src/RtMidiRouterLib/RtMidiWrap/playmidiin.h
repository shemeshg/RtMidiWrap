#pragma once
#include <memory>
#include "playmidi.h"
#include "songposition.h"
#include "midievent.h"


namespace RtMidiWrap {



class PlayMidiIn:public PlayMidi
{
public:
    std::unique_ptr<MidiIn> midiin;

    PlayMidiIn();
    virtual ~PlayMidiIn() = default;
    SongPosition songposition;

    virtual void callback( double deltatime, std::vector< BYTE> &message,int portNumber, std::string portName);
    virtual void listener(MidiEvent &m);
    virtual void clockAction(double barPosition, double spp,double barPositionNoReset, double sppNoReset){
        UNUSED(barPosition);
        UNUSED(spp);
        UNUSED(barPositionNoReset);
        UNUSED(sppNoReset);
    };
    void ignoreTypes( bool midiSysex = true,bool midiTime = true, bool midiSense = true);







};
}


