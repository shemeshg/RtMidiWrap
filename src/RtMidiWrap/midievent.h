#ifndef MIDIEVENT_H
#define MIDIEVENT_H
#include "common.h"
//#include <string>



namespace RtMidiWrap {
enum EVENT_STATUS {
    OK,
    DELETED,
    DEFFERED
};

enum DEFFERED_EVENT_TYPE {
    IN_SPP,
    IN_BAR,
    AT_SPP,
    AT_BAR,
    QUANTIZE_SPP,
    QUANTIZE_BAR
};

class MidiEvent:public CommonStatic
{
public:
    MidiEvent(double deltatime, std::vector< BYTE> &data,int portNumber, std::string &portName);

    void updateProperties();
    EVENT_STATUS eventStatus = EVENT_STATUS::OK;

    int cc14bitLsb;

    std::vector< BYTE> &data;
    double deltatime;
    int channel = 0;
    int command = 0;
    std::string commandStr;
    int data1 = 0;
    int data2 = 0;
    MIDI_MSG_TYPE msgtype;
    int portNumber;
    std::string &portName;

    DEFFERED_EVENT_TYPE defferedEventType = DEFFERED_EVENT_TYPE::IN_SPP;
    double defferedSubmittedAt = 0;
    double defferedTo = 0;
    int defferedFilterChainId = 0;
    int defferedFilterId = 0;
};
}
#endif // MIDIEVENT_H
