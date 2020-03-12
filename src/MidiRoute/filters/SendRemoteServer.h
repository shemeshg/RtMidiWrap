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


    std::unique_ptr<SignalSlotClass> giliSlotClass;
    std::unique_ptr<SignalClass> giliSignalClass;

    SendRemoteServer(Webchannel::EmitCommand &ec,std::string serverName, int serverPort, int remoteMidiPortNumber):
        serverName{serverName},serverPort{serverPort},remoteMidiPortNumber{remoteMidiPortNumber},ec{ec}  {

        giliSlotClass = std::unique_ptr<SignalSlotClass>(new SignalSlotClass()) ;
        giliSlotClass->openConnection(QString::fromStdString(serverName),serverPort, remoteMidiPortNumber);
        giliSignalClass =  std::unique_ptr< SignalClass>( new SignalClass( *giliSlotClass.get() ) );
    };

    void doFilter(RtMidiWrap::MidiEvent &in) override{
        //giliSignalClass->doTest("Still ok\n");
        giliSignalClass->sendRemoteServer(in,serverName, serverPort, remoteMidiPortNumber);
        //ec.sendRemoteServer(in,serverName, serverPort, remoteMidiPortNumber);
    };


};

}



#endif // SENDREMOTESERVER_H
