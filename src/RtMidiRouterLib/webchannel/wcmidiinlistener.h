#pragma once
#include "MidiRoute/midiroute.h"
#include "EmitCommand.h"
#include "WcRouteFilterChains.h"

namespace Webchannel {


class WcMidiInListener:public MidiRoute::MidiInRouter{
public:
    EmitCommand &ec;
    //std::unique_ptr<WcRouteFilterChains> wrfc = unique_ptr<WcRouteFilterChains>(new WcRouteFilterChains());


    std::vector<int> propegateClockToOtherMidiIns {};

    ~WcMidiInListener(){
        clearRoutingMidiChains();
    }


    void clearRoutingMidiChains(){
        routeFilterChains->chains.clear();
        clearCc14Bit();
        propegateClockToOtherMidiIns.clear();
        defferedMidiEvents.clear();
    }

    WcMidiInListener(EmitCommand &ec): ec{ec}{
        //int i = ec.routeFilterChains->addChain();
        //ec.routeFilterChains->chains[i]->addSendMidiPort("IAC Driver Bus 1");
    };

    void clockAction(double barPosition, double spp, double barPositionNoReset, double sppNoReset){
        for (auto &channelId : propegateClockToOtherMidiIns){
            ec.propegateClock(channelId, barPosition, spp, barPositionNoReset, sppNoReset);
        }

        bool found = false;
        for (unsigned i=0; i<defferedMidiEvents.size(); ++i){
            auto m = defferedMidiEvents[i].get();
             if (m->defferedEventType == RtMidiWrap::DEFFERED_EVENT_TYPE::AT_SPP && m->defferedTo <= spp){
                m->eventStatus = RtMidiWrap::EVENT_STATUS::OK;
                found = true;
            }
            if (m->defferedEventType == RtMidiWrap::DEFFERED_EVENT_TYPE::IN_SPP && (m->defferedTo + m->defferedSubmittedAt) <= sppNoReset){
                m->eventStatus = RtMidiWrap::EVENT_STATUS::OK;
                found = true;
            }
            if (m->defferedEventType == RtMidiWrap::DEFFERED_EVENT_TYPE::AT_BAR && m->defferedTo <= barPosition){
                m->eventStatus = RtMidiWrap::EVENT_STATUS::OK;
                found = true;
            }
            if (m->defferedEventType == RtMidiWrap::DEFFERED_EVENT_TYPE::IN_BAR && (m->defferedTo + m->defferedSubmittedAt) <= barPositionNoReset){
                m->eventStatus = RtMidiWrap::EVENT_STATUS::OK;
                found = true;
            }
        }

        if (!found){return;}

        for (unsigned i=0; i<defferedMidiEvents.size(); ++i){
            auto m = defferedMidiEvents[i].get();
            if (m->eventStatus == RtMidiWrap::EVENT_STATUS::OK){
                   unsigned int nBytesFilters = (unsigned int)routeFilterChains->chains[m->defferedFilterChainId]->filterMidiChannelMsgAry.size();
                   for ( unsigned int i_filters= (m->defferedFilterId+1) ; i_filters<nBytesFilters; i_filters++ ){
                        routeFilterChains->chains[m->defferedFilterChainId]->filterMidiChannelMsgAry[i_filters]->doFilter(*m);
                   }
                   m->eventStatus = RtMidiWrap::EVENT_STATUS::DELETED;
            }
        }


        defferedMidiEvents.erase(
              std::remove_if(
                  defferedMidiEvents.begin(),
                  defferedMidiEvents.end(),
                  [&] (std::unique_ptr<RtMidiWrap::MidiEvent> const& m)
                  {
                      return m->eventStatus  == RtMidiWrap::EVENT_STATUS::DELETED;
                  }),
              defferedMidiEvents.end()
              );



    }


    /*
    void listener(RtMidiWrap::MidiEvent &m){
        ec.msgSend(m);
    }
    */

};
}


