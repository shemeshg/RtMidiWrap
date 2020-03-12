//#include "src/RtMidiWrap/RtMidiWrap.h"
//#include "src/RtMidiWrap/midievent.h"
#include "src/MidiRoute/midiroute.h"
//#include "src/MidiRoute/routfilter.h"
//#include "src/MidiRoute/rangemap.h"

namespace MidiRoute {
void filterMidiChannelMsg(RtMidiWrap::MidiEvent &in, RangeMap &fromChannel, RangeMap &fromCommand, RangeMap &fromData1, RangeMap &fromData2,
                           MIDI_FILTER_ACTION_IF_NOT deleteIfNot
                          ){
    bool passedFromFilter = true;
    if (in.msgtype == RtMidiWrap::MIDI_MSG_TYPE::MIDI_CHANNEL_MESSAGES ){
        std::vector<BYTE> sndVector = {0,0,0};
        int old_command = in.data[0] >> 4;
        int new_command = old_command;
        passedFromFilter = passedFromFilter && fromCommand.isInRange( old_command);
        if (fromCommand.isInRange( old_command)){new_command = fromCommand.getVal(old_command);}

        int old_channel = in.channel;
        int new_channel = old_channel;
        passedFromFilter = passedFromFilter && fromChannel.isInRange( old_channel);
        if ( fromChannel.isInRange( old_channel) ){new_channel = fromChannel.getVal(old_channel);}


        int old_data1 = in.data[1];
        int new_data1 = old_data1;
        passedFromFilter = passedFromFilter && fromData1.isInRange(old_data1);
        if (fromData1.isInRange(old_data1)){new_data1 = fromData1.getVal(old_data1);}


        int old_data2 = in.data[2];
        int new_data2 = old_data2;

        passedFromFilter = passedFromFilter && fromData2.isInRange(old_data2);
        if (fromData2.isInRange(old_data2)){new_data2 = fromData2.getVal(old_data2);}

        // destination within boundaries
        passedFromFilter = passedFromFilter && new_data2 > 0 && new_data1 > 0 && new_channel > 0 && new_command > 0 &&
          new_data2 <= fromData2.H_BOUND && new_data1 <= fromData1.H_BOUND && new_channel <= fromChannel.H_BOUND && new_command <= fromCommand.H_BOUND;

        if (deleteIfNot == MIDI_FILTER_ACTION_IF_NOT::DELETE_IF_NOT  && !passedFromFilter){
            in.eventStatus = RtMidiWrap::EVENT_STATUS::DELETED;
        }
        else if (deleteIfNot == MIDI_FILTER_ACTION_IF_NOT::DELETE_IF_IS  && passedFromFilter){
            in.eventStatus = RtMidiWrap::EVENT_STATUS::DELETED;
        }
        else {
            if (passedFromFilter){
                sndVector[0] = (new_command<<4) + (new_channel -1) ;

                sndVector[1] = new_data1;
                sndVector[2] = new_data2;

                if(new_command == RtMidiWrap::CommonStatic::MIDI_CHANNEL_MESSAGES::channelaftertouch){
                    sndVector[1] = sndVector[2];
                    // There should not be sndVector[2] in channelaftertouch
                    sndVector.pop_back();
                }

                if(new_command == RtMidiWrap::CommonStatic::MIDI_CHANNEL_MESSAGES::pitchbend ){
                        sndVector[1] = in.cc14bitLsb;
                }


                in.data = sndVector;
                in.updateProperties();
            }





        }



    }

}
}
