#ifndef WCMIDIIN_H
#define WCMIDIIN_H

#include <QObject>
#include <QStringList>
#include <QVariantMap>
#include <QVariantList>
#include <QVector>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QWebSocket>
#include "src/MidiRoute/rangemap.h"
#include "src/webchannel/wcmidiinlistener.h"
#include "libs/QWebchannelCppClient/WebChannelClient.h"
#include "virtualinout.h"

namespace Webchannel {

class WcMidiIn : public QObject,EmitCommand
{
    Q_OBJECT
private:
    void _setRangeMap(MidiRoute::RangeMap &range, QJsonArray &json){
        range.clear();


        for(QJsonValue v: json){
            QJsonArray j =  v.toArray();
            std::vector<int> intAry;
            for(auto i = j.begin(); i != j.end(); i++) {
                intAry.push_back(i->toInt());
            }
            setRangeMapObject(intAry,range);
        }
    }

protected:
    // For general requests like midi list ports
    std::unique_ptr<WcMidiInListener> midiin;
    //std::unique_ptr<MidiRoute::MidiFilterChain> routeFilterChains = std::unique_ptr<MidiRoute::MidiFilterChain>(new MidiRoute::MidiFilterChain());

    // Opened ins
    std::map<int, std::unique_ptr<WcMidiInListener>> openedMidiInObj;

    std::map<std::string, std::unique_ptr<CWebChannelClient>> opendRemoteServers;
    std::map<std::string, std::unique_ptr<QWebSocket>> opendRemoteServersSockets;


public:
    explicit WcMidiIn(QObject *parent = nullptr);

    void msgSend(RtMidiWrap::MidiEvent &m,LOG_TO logto, std::string userdata);

    void propegateClock(int portNumber, double barPosition, double spp, double barPositionNoReset, double sppNoReset){

        openedMidiInObj[portNumber]->clockAction(barPosition, spp, barPositionNoReset, sppNoReset);

    }

public:
    Q_INVOKABLE bool msgToServer(const QString &msg);
    Q_INVOKABLE int getPortCount();
    Q_INVOKABLE QString getPortName(int i);
    Q_INVOKABLE int getPortNumber(const QString &s);
    Q_INVOKABLE QVariantMap getPorts();
    Q_INVOKABLE QVariantMap getOpenedPorts();

    Q_INVOKABLE void openPort( int portNumber) ;
    Q_INVOKABLE void openVirtualPort(const QString &s);
    Q_INVOKABLE void openVirtualInOutPort(const QString &s){
        addVirtualInOutPort(s.toStdString());
    }

    // these functions assume openedMidiOutObj[portNumber] exists
    Q_INVOKABLE bool isPortOpen( int portNumber);
    Q_INVOKABLE void ignoreTypes( int portNumber, bool midiSysex = true,bool midiTime = true, bool midiSense = true){
        openedMidiInObj[portNumber]->midiin->ignoreTypes(midiSysex, midiTime, midiSense);
    }

    Q_INVOKABLE void addCc14Bit( int portNumber, int channel, int cc){
        openedMidiInObj[portNumber]->addCc14Bit(channel, cc);
    }
    Q_INVOKABLE void clearCc14Bit( int portNumber){
        openedMidiInObj[portNumber]->clearCc14Bit();
    }

    Q_INVOKABLE void addPropegateClockPort( int portNumber, int portNumberToPropegate){
        openedMidiInObj[portNumber]->propegateClockToOtherMidiIns.push_back(portNumberToPropegate);
    }
    Q_INVOKABLE void clearPropegateClockPort( int portNumber){
        openedMidiInObj[portNumber]->propegateClockToOtherMidiIns.clear();
    }

    Q_INVOKABLE void setTimeSig( int portNumber, double timeSig, double timeSigDivBy, double fromSppPos){
        openedMidiInObj[portNumber]->songposition.timeSig = timeSig;
        openedMidiInObj[portNumber]->songposition.timeSigDivBy = timeSigDivBy;
        openedMidiInObj[portNumber]->songposition.fromSppPos = fromSppPos;
    }

    Q_INVOKABLE void restart(){
        midiin.reset(new WcMidiInListener(*this));

        openedMidiInObj.clear();
        opendRemoteServers.clear();
        opendRemoteServersSockets.clear();
    }

    Q_INVOKABLE void clearRoutingMidiChains(int portNumber){
        openedMidiInObj[portNumber]->clearRoutingMidiChains();
    }

    Q_INVOKABLE int routingMidiChainsAaddChain(int portNumber){
        return openedMidiInObj[portNumber]->routeFilterChains->addChain();
    }
    Q_INVOKABLE int routingActionAddSendPortByName(int portNumber, int chainId, QString portName){
        openedMidiInObj[portNumber]->routeFilterChains->chains[chainId]->addSendMidiPort(portName.toStdString());
        return (int)openedMidiInObj[portNumber]->routeFilterChains->chains.size() - 1;
    }
    Q_INVOKABLE int routingActionAddSendPortByNumber(int portNumber, int chainId, int portNumberOut){
        openedMidiInObj[portNumber]->routeFilterChains->chains[chainId]->addSendMidiPort(portNumberOut);
        return (int)openedMidiInObj[portNumber]->routeFilterChains->chains.size() - 1;
    }

    Q_INVOKABLE int routingActionAddSendRemoteServer(int portNumber, int chainId, QString serverName, int serverPort, int remoteMidiPortNumber){
        openedMidiInObj[portNumber]->routeFilterChains->chains[chainId]->addSendRemoteServer(*this, serverName.toStdString(), serverPort, remoteMidiPortNumber);

        return (int)openedMidiInObj[portNumber]->routeFilterChains->chains.size() - 1;
    }

    Q_INVOKABLE int routingActionAddLogData(int portNumber, int chainId, int logto, QString userdata){
        openedMidiInObj[portNumber]->routeFilterChains->chains[chainId]->addLogData(*this,(LOG_TO)logto, userdata.toStdString());
        return (int)openedMidiInObj[portNumber]->routeFilterChains->chains.size() - 1;
    }
    Q_INVOKABLE int routingActionAddDeferedEvent(int portNumber, int chainId, int defferedEventType,double defferedTo){
        openedMidiInObj[portNumber]->routeFilterChains->chains[chainId]->addDeferedEvent((RtMidiWrap::DEFFERED_EVENT_TYPE)defferedEventType,defferedTo );
        return (int)openedMidiInObj[portNumber]->routeFilterChains->chains.size() - 1;
    }


    Q_INVOKABLE int routingActionAddFilterMidiChannelMsg(int portNumber, int chainId,
                                                         QJsonArray channels, QJsonArray eventTypes, QJsonArray data1, QJsonArray data2, int midiFilterActionIfNot){

        MidiRoute::RangeMap _channels;
        _setRangeMap(_channels, channels);
        MidiRoute::RangeMap _eventTypes;
        _setRangeMap(_eventTypes, eventTypes);
        MidiRoute::RangeMap _data1;
        _setRangeMap(_data1, data1);
        MidiRoute::RangeMap _data2;
        _setRangeMap(_data2, data2);

        openedMidiInObj[portNumber]->routeFilterChains->chains[chainId]->addFilterMidiChannelMsg(_channels,_eventTypes, _data1, _data2,
                                                                                                (MidiRoute::MIDI_FILTER_ACTION_IF_NOT)midiFilterActionIfNot );

        return (int)openedMidiInObj[portNumber]->routeFilterChains->chains.size() - 1;

    }

signals:
    bool msgToClient(QString msg);
    bool dataToClient(QString msg);

};
}

#endif // WCMIDIIN_H
