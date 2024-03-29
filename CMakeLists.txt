cmake_minimum_required(VERSION 3.5)

project(RtMidiRoute VERSION 1.4.0 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


configure_file("${PROJECT_SOURCE_DIR}/config.h.in" "${PROJECT_SOURCE_DIR}/config.h")

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets LinguistTools REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets LinguistTools REQUIRED)

set(TS_FILES RtMidiRoute_en_US.ts)
set(APP_ICON_RESOURCE_WINDOWS "${CMAKE_CURRENT_SOURCE_DIR}/rc.qrc")

add_subdirectory(src/RtMidiRouterLib)

set(PROJECT_SOURCES
    main.cpp
    src/uimain.cpp
    src/RtMidiRouterLib/mainclass.h
    src/uimain.h    
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

target_link_libraries(RtMidiRoute PRIVATE Qt${QT_VERSION_MAJOR}::Widgets 
    RtMidiRouterLib
    )

set_target_properties(RtMidiRoute PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER MidiRouter.shemeshg.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    OUTPUT_NAME "Midi router server"
)



if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(RtMidiRoute)
endif()
