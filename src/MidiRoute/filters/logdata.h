#ifndef LOGDATA_H
#define LOGDATA_H
#include "src/MidiRoute/routfilter.h"
#include "src/webchannel/EmitCommand.h"

namespace MidiRoute {



class LogData:public RoutFilter
{
public:
    Webchannel::EmitCommand &ec;
    Webchannel::LOG_TO logto;



    ~LogData() { };
    LogData(Webchannel::EmitCommand &ec, Webchannel::LOG_TO logto): ec{ec},logto{logto} {        
    };



    void doFilter(RtMidiWrap::MidiEvent &in) override{
         ec.msgSend(in,logto);
    };
};
}
#endif // LOGDATA_H
