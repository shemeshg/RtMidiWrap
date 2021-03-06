#ifndef SENDREMOTESERVER_H
#define SENDREMOTESERVER_H
#include "src/MidiRoute/routfilter.h"
#include "src/webchannel/EmitCommand.h"
#include "src/webchannel/SignalSlot.h"

namespace MidiRoute {

class SendRemoteServer:public RoutFilter{
    //
public:
    ~SendRemoteServer() { };
    std::string serverName;
    int serverPort, remoteMidiPortNumber;
    Webchannel::EmitCommand &ec;


    std::unique_ptr<SignalSlotClass> slotClass;
    std::unique_ptr<SignalClass> signalClass;

    SendRemoteServer(Webchannel::EmitCommand &ec,std::string serverName, int serverPort, int remoteMidiPortNumber):
        serverName{serverName},serverPort{serverPort},remoteMidiPortNumber{remoteMidiPortNumber},ec{ec}  {

        slotClass = std::unique_ptr<SignalSlotClass>(new SignalSlotClass()) ;
        slotClass->openConnection(QString::fromStdString(serverName),serverPort, remoteMidiPortNumber);
        signalClass =  std::unique_ptr< SignalClass>( new SignalClass( *slotClass.get() ) );
    };

    void doFilter(RtMidiWrap::MidiEvent &in) override{
        signalClass->sendRemoteServer(in,serverName, serverPort, remoteMidiPortNumber);
    };


};

}



#endif // SENDREMOTESERVER_H
