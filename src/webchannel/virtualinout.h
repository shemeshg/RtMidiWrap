#ifndef VIRTUALINOUT_H
#define VIRTUALINOUT_H


#include "src/RtMidiWrap/RtMidiWrap.h"
#include <string>


void virtualInOutPortCallback( double deltatime, std::vector< unsigned char > *message, void *userData );

class VirtualInOut {
public:
    RtMidiIn *midiinVirtual = new RtMidiIn();
    RtMidiOut *midioutVirtual = new RtMidiOut();
    void addVirtualInOutPort(std::string portname);
};



void addVirtualInOutPort(std::string portname);

#endif // VIRTUALINOUT_H
