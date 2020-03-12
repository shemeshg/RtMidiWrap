#include "midiroute.h"
#include <string>

//#include "src/RtMidiWrap/RtMidiWrap.h"
//#include "src/RtMidiWrap/playmidiout.h"
//#include "src/RtMidiWrap/playmidiin.h"
//#include "src/RtMidiWrap/midievent.h"
//#include "src/RtMidiWrap/common.h"

//#include "filters/FilterMidiChannelMsg.h"
//#include "filters/sendmidiport.h"
//#include "midifilterchain.h"
//#include "rangemap.h"

using namespace std;

namespace MidiRoute {



void MidiInRouter::listener(RtMidiWrap::MidiEvent &m){


    for  (int &cc14item:cc14Bit)
    {

        int channelCc = m.channel *1000 + m.data1;
        if(m.command == RtMidiWrap::CommonStatic::MIDI_CHANNEL_MESSAGES::controlchange &&
                channelCc == cc14item ){

            msbForCc14Bit[channelCc] = m.data2;
            return;
        }

        if(m.command == RtMidiWrap::CommonStatic::MIDI_CHANNEL_MESSAGES::controlchange &&
                channelCc == cc14item + 32){
            m.cc14bitLsb = m.data2;
            m.data1 = m.data1 - 32;
            m.data2 = msbForCc14Bit[channelCc - 32];
            m.data[1] = m.data1;
            m.data[2] = m.data2;
        }



    }


    // Force copy operation for vector
    std::vector< BYTE> mData;
    for (unsigned i=0; i<m.data.size(); i++)
            mData.push_back(m.data[i]);

    unsigned int nBytesChains = routeFilterChains->chains.size();



    for ( unsigned int i_chain=0; i_chain<nBytesChains; i_chain++ ){
        RtMidiWrap::MidiEvent copyOfM = m;
        unsigned int nBytesFilters = routeFilterChains->chains[i_chain]->filterMidiChannelMsgAry.size();



        std::vector< BYTE> copyOfData = mData;
        copyOfM.data  = copyOfData;


        for ( unsigned int i_filters=0; i_filters<nBytesFilters; i_filters++ ){
            if( copyOfM.eventStatus == RtMidiWrap::EVENT_STATUS::OK) {
                routeFilterChains->chains[i_chain]->filterMidiChannelMsgAry[i_filters]->doFilter(copyOfM);
            }
            if( copyOfM.eventStatus == RtMidiWrap::EVENT_STATUS::DEFFERED){
                copyOfM.defferedFilterChainId = i_chain;
                copyOfM.defferedFilterId = i_filters;
                if (copyOfM.defferedEventType == RtMidiWrap::DEFFERED_EVENT_TYPE::QUANTIZE_SPP){
                    copyOfM.defferedSubmittedAt = songposition.sppNoReset;
                    copyOfM.defferedEventType = RtMidiWrap::DEFFERED_EVENT_TYPE::IN_SPP;
                    int quantizeDiv = (songposition.spp / copyOfM.defferedTo);
                    int quantizeAfterPosition = (quantizeDiv + 1) * copyOfM.defferedTo ;
                    copyOfM.defferedTo = ((double)quantizeAfterPosition - songposition.spp);
                }
                if (copyOfM.defferedEventType == RtMidiWrap::DEFFERED_EVENT_TYPE::QUANTIZE_BAR){
                    copyOfM.defferedSubmittedAt = songposition.getBarPositionNoReset();
                    copyOfM.defferedEventType = RtMidiWrap::DEFFERED_EVENT_TYPE::IN_BAR;
                    int quantizeDiv = (songposition.getBarPosition() / copyOfM.defferedTo);
                    int quantizeAfterPosition = (quantizeDiv + 1) * copyOfM.defferedTo ;
                    copyOfM.defferedTo = ((double)quantizeAfterPosition - songposition.getBarPosition());
                }
                if (copyOfM.defferedEventType == RtMidiWrap::DEFFERED_EVENT_TYPE::AT_SPP){
                    copyOfM.defferedSubmittedAt = songposition.spp;
                }
                if(copyOfM.defferedEventType == RtMidiWrap::DEFFERED_EVENT_TYPE::IN_SPP){
                    copyOfM.defferedSubmittedAt = songposition.sppNoReset;
                }
                if (copyOfM.defferedEventType == RtMidiWrap::DEFFERED_EVENT_TYPE::AT_BAR){
                    copyOfM.defferedSubmittedAt = songposition.getBarPosition();
                }
                if(copyOfM.defferedEventType == RtMidiWrap::DEFFERED_EVENT_TYPE::IN_BAR){
                    copyOfM.defferedSubmittedAt = songposition.getBarPositionNoReset();
                }
                RtMidiWrap::MidiEvent defferedCopyOfM = copyOfM;
                defferedMidiEvents.push_back(std::make_unique<RtMidiWrap::MidiEvent>(defferedCopyOfM));
                copyOfM.eventStatus = RtMidiWrap::EVENT_STATUS::DELETED;
            }
        }
    }


}


}
