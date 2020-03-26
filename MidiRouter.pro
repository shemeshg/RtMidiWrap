TEMPLATE = app
CONFIG += console c++11
# CONFIG -= app_bundle
# no need qt ui # CONFIG -= qt

# add websockets
QT       += core websockets webchannel
QT       -= gui
CONFIG   += console


macx: LIBS += -framework CoreMIDI -framework CoreAudio -framework CoreFoundation
macx: DEFINES += __MACOSX_CORE__

unix:!macx: LIBS += -lasound -lpthread
unix:!macx: DEFINES += __LINUX_ALSA__

SOURCES += \
        libs/QWebchannelCppClient/WebChannelClient.cpp \
        libs/websocket/websocketclientwrapper.cpp \
        libs/websocket/websockettransport.cpp \
        main.cpp \
        src/MidiRoute/filters/FilterMidiChannelMsg.cpp \
        src/MidiRoute/filters/logdata.cpp \
        src/MidiRoute/midiroute.cpp \
        src/MidiRoute/rangemap.cpp \
        src/RtMidiWrap/RtMidiWrap.cpp \
        src/RtMidiWrap/common.cpp \
        src/RtMidiWrap/midievent.cpp \
        src/RtMidiWrap/playmidi.cpp \
        src/RtMidiWrap/playmidiin.cpp \
        src/RtMidiWrap/playmidiout.cpp \
        src/RtMidiWrap/songposition.cpp \
        src/webchannel/wcmidiin.cpp \
        src/webchannel/wcmidiout.cpp \
        src/webchannel/wcuserdata.cpp

HEADERS += \
    libs/QWebchannelCppClient/WebChannelClient.h \
    libs/websocket/websocketclientwrapper.h \
    libs/websocket/websockettransport.h \
    src/MidiRoute/RoutFiltersChainClass.h \
    src/MidiRoute/filters/FilterMidiChannelMsg.h \
    src/MidiRoute/filters/SendRemoteServer.h \
    src/MidiRoute/filters/defferedevent.h \
    src/MidiRoute/filters/logdata.h \
    src/MidiRoute/filters/sendmidiport.h \
    src/MidiRoute/make_unique.h \
    src/MidiRoute/midifilterchain.h \
    src/MidiRoute/midiroute.h \
    src/MidiRoute/rangemap.h \
    src/MidiRoute/routfilter.h \
    src/RtMidiWrap/RtMidiWrap.h \
    src/RtMidiWrap/common.h \
    src/RtMidiWrap/midievent.h \
    src/RtMidiWrap/playmidi.h \
    src/RtMidiWrap/playmidiin.h \
    src/RtMidiWrap/playmidiout.h \
    src/RtMidiWrap/songposition.h \
    src/webchannel/EmitCommand.h \
    src/webchannel/SignalSlot.h \
    src/webchannel/WcRouteFilterChains.h \
    src/webchannel/wcmidiin.h \
    src/webchannel/wcmidiinlistener.h \
    src/webchannel/wcmidiout.h \
    src/webchannel/wcuserdata.h









unix:!macx: LIBS += -L/usr/lib/x86_64-linux-gnu/ -lrtmidi
unix:!macx: INCLUDEPATH += /usr/include/rtmidi
unix:!macx: DEPENDPATH += /usr/include/rtmidi



# **** static link
# macx: LIBS += -L/usr/local/Cellar/rtmidi/4.0.0/lib/ -lrtmidi
# macx: PRE_TARGETDEPS += /usr/local/Cellar/rtmidi/4.0.0/lib/librtmidi.a

# **** dynamic link
macx: LIBS += -L/usr/local/Cellar/rtmidi/4.0.0/lib/ -lrtmidi.5


# **** dynamic and static link
macx: INCLUDEPATH += /usr/local/Cellar/rtmidi/4.0.0/include
macx: DEPENDPATH += /usr/local/Cellar/rtmidi/4.0.0/include

