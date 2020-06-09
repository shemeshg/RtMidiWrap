TEMPLATE = app
CONFIG += console c++11
# CONFIG -= app_bundle
# no need qt ui # CONFIG -= qt

# add websockets
QT       += core websockets webchannel \
    widgets
QT       -= gui
CONFIG   += console

macx: ICON = icon.icns
win32: RC_ICONS = icon.ico
TARGET = "Midi router server"

macx: LIBS += -framework CoreMIDI -framework CoreAudio -framework CoreFoundation
macx: DEFINES += __MACOSX_CORE__

unix:!macx: LIBS += -lasound -lpthread
unix:!macx: DEFINES += __LINUX_ALSA__

win32: LIBS += -lwinmm
win32: DEFINES += __WINDOWS_MM__

SOURCES += \
        libs/QWebchannelCppClient/WebChannelClient.cpp \
        libs/rtmidi/RtMidi.cpp \
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
        src/mainclass.cpp \
        src/uimain.cpp \
        src/webchannel/virtualinout.cpp \
        src/webchannel/wcmidiin.cpp \
        src/webchannel/wcmidiout.cpp \
        src/webchannel/wcuserdata.cpp

HEADERS += \
    libs/QWebchannelCppClient/WebChannelClient.h \
    libs/rtmidi/RtMidi.h \
    libs/websocket/websocketclientwrapper.h \
    libs/websocket/websockettransport.h \
    src/MidiRoute/RoutFiltersChainClass.h \
    src/MidiRoute/filters/FilterMidiChannelMsg.h \
    src/MidiRoute/filters/SendRemoteServer.h \
    src/MidiRoute/filters/defferedevent.h \
    src/MidiRoute/filters/logdata.h \
    src/MidiRoute/filters/sendmidiport.h \
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
    src/mainclass.h \
    src/uimain.h \
    src/webchannel/EmitCommand.h \
    src/webchannel/SignalSlot.h \
    src/webchannel/WcRouteFilterChains.h \
    src/webchannel/virtualinout.h \
    src/webchannel/wcmidiin.h \
    src/webchannel/wcmidiinlistener.h \
    src/webchannel/wcmidiout.h \
    src/webchannel/wcuserdata.h

RESOURCES += \
    rc.qrc











