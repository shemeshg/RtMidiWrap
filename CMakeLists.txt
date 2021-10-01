cmake_minimum_required(VERSION 3.5)

project(RtMidiRoute VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets LinguistTools WebSockets WebChannel REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets LinguistTools WebSockets WebChannel REQUIRED)

set(TS_FILES RtMidiRoute_en_US.ts)
set(APP_ICON_RESOURCE_WINDOWS "${CMAKE_CURRENT_SOURCE_DIR}/rc.qrc")


set(PROJECT_SOURCES
    libs/QWebchannelCppClient/WebChannelClient.cpp
    libs/rtmidi/RtMidi.cpp
    libs/websocket/websocketclientwrapper.cpp
    libs/websocket/websockettransport.cpp
    main.cpp
    src/MidiRoute/filters/FilterMidiChannelMsg.cpp
    src/MidiRoute/filters/logdata.cpp
    src/MidiRoute/midiroute.cpp
    src/MidiRoute/rangemap.cpp
    src/RtMidiWrap/RtMidiWrap.cpp
    src/RtMidiWrap/common.cpp
    src/RtMidiWrap/midievent.cpp
    src/RtMidiWrap/playmidi.cpp
    src/RtMidiWrap/playmidiin.cpp
    src/RtMidiWrap/playmidiout.cpp
    src/RtMidiWrap/songposition.cpp
    src/mainclass.cpp
    src/uimain.cpp
    src/webchannel/virtualinout.cpp
    src/webchannel/wcmidiin.cpp
    src/webchannel/wcmidiout.cpp
    src/webchannel/wcuserdata.cpp
    libs/QWebchannelCppClient/WebChannelClient.h
    libs/rtmidi/RtMidi.h
    libs/websocket/websocketclientwrapper.h
    libs/websocket/websockettransport.h
    src/MidiRoute/RoutFiltersChainClass.h
    src/MidiRoute/filters/FilterMidiChannelMsg.h
    src/MidiRoute/filters/SendRemoteServer.h
    src/MidiRoute/filters/defferedevent.h
    src/MidiRoute/filters/logdata.h
    src/MidiRoute/filters/sendmidiport.h
    src/MidiRoute/midifilterchain.h
    src/MidiRoute/midiroute.h
    src/MidiRoute/rangemap.h
    src/MidiRoute/routfilter.h
    src/RtMidiWrap/RtMidiWrap.h
    src/RtMidiWrap/common.h
    src/RtMidiWrap/midievent.h
    src/RtMidiWrap/playmidi.h
    src/RtMidiWrap/playmidiin.h
    src/RtMidiWrap/playmidiout.h
    src/RtMidiWrap/songposition.h
    src/mainclass.h
    src/uimain.h
    src/webchannel/EmitCommand.h
    src/webchannel/SignalSlot.h
    src/webchannel/WcRouteFilterChains.h
    src/webchannel/virtualinout.h
    src/webchannel/wcmidiin.h
    src/webchannel/wcmidiinlistener.h
    src/webchannel/wcmidiout.h
    src/webchannel/wcuserdata.h
        ${TS_FILES}
        ${APP_ICON_RESOURCE_WINDOWS}
)




qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})

if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    set(MACOSX TRUE)
endif()
if(UNIX AND NOT APPLE)
    set(LINUX TRUE)
endif()
if(WIN32 OR MSVC OR MSYS OR MINGW)
    set(WINDOWS TRUE)
endif()

if(MACOSX)
    #RtMidi lib dependencies
    find_library(COREMIDI_LIBRARY CoreMIDI)
    find_library(COREAUDIO_LIBRARY CoreAudio)
    find_library(COREFOUNDATION_LIBRARY CoreFoundation)

    list(APPEND OsSpecificLibs
        ${COREFOUNDATION_LIBRARY}
        ${COREAUDIO_LIBRARY}
        ${COREMIDI_LIBRARY}
        )

    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D__MACOSX_CORE__")
    set(TARGET_OS_IPHONE 0)

    # Application icon
    set(MACOSX_BUNDLE_ICON_FILE icon.icns)
    set(APP_ICON_MACOSX ${CMAKE_CURRENT_SOURCE_DIR}/icon.icns)
    set_source_files_properties(${APP_ICON_MACOSX} PROPERTIES
           MACOSX_PACKAGE_LOCATION "Resources")
endif()

qt_add_executable(RtMidiRoute MACOSX_BUNDLE
    MANUAL_FINALIZATION
    ${PROJECT_SOURCES}
    ${APP_ICON_MACOSX}
)

target_link_libraries(RtMidiRoute PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::WebSockets Qt${QT_VERSION_MAJOR}::WebChannel
    ${OsSpecificLibs}
    )

set_target_properties(RtMidiRoute PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER MidiRouter.shemeshg.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
)



if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(RtMidiRoute)
endif()
