#pragma once
#include "src/MidiRoute/routfilter.h"
namespace MidiRoute {
class DefferedEvent:public RoutFilter
{
public:
    RtMidiWrap::DEFFERED_EVENT_TYPE defferedEventType;
    double defferedTo;

    ~DefferedEvent() { };
    DefferedEvent(RtMidiWrap::DEFFERED_EVENT_TYPE defferedEventType, double defferedTo): defferedEventType{defferedEventType},defferedTo{defferedTo} {
    };



    void doFilter(RtMidiWrap::MidiEvent &in) override{
        in.eventStatus =  RtMidiWrap::EVENT_STATUS::DEFFERED;
        in.defferedEventType = defferedEventType;
        in.defferedTo = defferedTo;

    };
};
}

