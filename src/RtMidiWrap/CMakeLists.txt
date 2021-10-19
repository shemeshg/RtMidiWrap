set(RtMidiWrap_SRCS
      RtMidiWrap.cpp
      common.cpp
      midievent.cpp
      playmidi.cpp
      playmidiin.cpp
      playmidiout.cpp
      libs/rtmidi/RtMidi.cpp
      RtMidiWrap.h
      common.h
      midievent.h
      playmidi.h
      playmidiin.h
      playmidiout.h
      songposition.h
      libs/rtmidi/RtMidi.h
)

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
    # https://stackoverflow.com/questions/4929255/building-static-libraries-on-mac-using-cmake-and-gcc
    SET(CMAKE_C_ARCHIVE_CREATE   "<CMAKE_AR> Scr <TARGET> <LINK_FLAGS> <OBJECTS>")
    SET(CMAKE_CXX_ARCHIVE_CREATE "<CMAKE_AR> Scr <TARGET> <LINK_FLAGS> <OBJECTS>")
    SET(CMAKE_C_ARCHIVE_FINISH   "<CMAKE_RANLIB> -no_warning_for_no_symbols -c <TARGET>")
    SET(CMAKE_CXX_ARCHIVE_FINISH "<CMAKE_RANLIB> -no_warning_for_no_symbols -c <TARGET>")

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

endif()

# Declare the library
add_library(RtMidiWrap STATIC
    ${RtMidiWrap_SRCS}
)

# Specify here the include directories exported
# by this library

target_include_directories(RtMidiWrap PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/src/RtMidiWrap"
)

target_link_libraries(RtMidiWrap PRIVATE
    ${OsSpecificLibs}
    )
