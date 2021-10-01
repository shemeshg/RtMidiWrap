#pragma once
#include "src/MidiRoute/routfilter.h"
#include "src/webchannel/EmitCommand.h"


namespace MidiRoute {



class LogData:public RoutFilter
{
public:
    Webchannel::EmitCommand &ec;
    Webchannel::LOG_TO logto;
    std::string userdata;


    ~LogData() { };
    LogData(Webchannel::EmitCommand &ec, Webchannel::LOG_TO logto, std::string userdata): ec{ec},logto{logto}, userdata{userdata} {
    };



    void doFilter(RtMidiWrap::MidiEvent &in) override{
         ec.msgSend(in,logto, userdata);
    };
};
}

