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

    std::unique_ptr<SignalSlotClass> slotClass;
    std::unique_ptr<SignalClass> signalClass;

    ~SendMidiPort() { };
    SendMidiPort(std::string portName){
        slotClass = std::unique_ptr<SignalSlotClass>(new SignalSlotClass()) ;
        slotClass->openPort(portName);
        signalClass =  std::unique_ptr< SignalClass>( new SignalClass( *slotClass.get() ) );
    };

    SendMidiPort(int portNumber){
        slotClass = std::unique_ptr<SignalSlotClass>(new SignalSlotClass()) ;
        slotClass->openPort(portNumber);
        signalClass =  std::unique_ptr< SignalClass>( new SignalClass( *slotClass.get() ) );

    };

    void doFilter(RtMidiWrap::MidiEvent &in) override{
         if (in.processNrpn && in.passedThrouFilter){
             vector<BYTE> c;
             c.push_back(in.channel);
             signalClass->doSetNonRegisteredParameterInt(in.nrpnControl, in.nrpnData, c);
         } else {
            signalClass->doSendMessage(in.data);
         }

    };


};

}



#endif // SENDMIDIPORT_H
