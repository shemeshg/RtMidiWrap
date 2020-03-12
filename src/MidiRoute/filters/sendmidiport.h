#ifndef SENDMIDIPORT_H
#define SENDMIDIPORT_H


//#include "src/RtMidiWrap/RtMidiWrap.h"
//#include "src/RtMidiWrap/midievent.h"
#include "src/MidiRoute/midiroute.h"
#include "src/MidiRoute/routfilter.h"
#include "src/webchannel/SignalSlot.h"

namespace MidiRoute {

class SendMidiPort:public RoutFilter{

public:

    std::unique_ptr<SignalSlotClass> giliSlotClass;
    std::unique_ptr<SignalClass> giliSignalClass;

    ~SendMidiPort() { };
    SendMidiPort(std::string portName){
        giliSlotClass = std::unique_ptr<SignalSlotClass>(new SignalSlotClass()) ;
        giliSlotClass->openPort(portName);
        giliSignalClass =  std::unique_ptr< SignalClass>( new SignalClass( *giliSlotClass.get() ) );
    };

    SendMidiPort(int portNumber){
        giliSlotClass = std::unique_ptr<SignalSlotClass>(new SignalSlotClass()) ;
        giliSlotClass->openPort(portNumber);
        giliSignalClass =  std::unique_ptr< SignalClass>( new SignalClass( *giliSlotClass.get() ) );

    };

    void doFilter(RtMidiWrap::MidiEvent &in) override{
         giliSignalClass->doSendMessage(in.data);
    };


};

}



#endif // SENDMIDIPORT_H
