# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.24

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.24.1/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.24.1/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Volumes/FAST/develop/MidiRouter/projects/RtMidiWrap

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Volumes/FAST/develop/MidiRouter/projects/RtMidiWrap/build

# Utility rule file for RtMidiLib_autogen.

# Include any custom commands dependencies for this target.
include src/RtMidiRouterLib/RtMidiWrap/libs/rtmidi/CMakeFiles/RtMidiLib_autogen.dir/compiler_depend.make

# Include the progress variables for this target.
include src/RtMidiRouterLib/RtMidiWrap/libs/rtmidi/CMakeFiles/RtMidiLib_autogen.dir/progress.make

src/RtMidiRouterLib/RtMidiWrap/libs/rtmidi/CMakeFiles/RtMidiLib_autogen:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/Volumes/FAST/develop/MidiRouter/projects/RtMidiWrap/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Automatic MOC and UIC for target RtMidiLib"
	cd /Volumes/FAST/develop/MidiRouter/projects/RtMidiWrap/build/src/RtMidiRouterLib/RtMidiWrap/libs/rtmidi && /usr/local/Cellar/cmake/3.24.1/bin/cmake -E cmake_autogen /Volumes/FAST/develop/MidiRouter/projects/RtMidiWrap/build/src/RtMidiRouterLib/RtMidiWrap/libs/rtmidi/CMakeFiles/RtMidiLib_autogen.dir/AutogenInfo.json Debug

RtMidiLib_autogen: src/RtMidiRouterLib/RtMidiWrap/libs/rtmidi/CMakeFiles/RtMidiLib_autogen
RtMidiLib_autogen: src/RtMidiRouterLib/RtMidiWrap/libs/rtmidi/CMakeFiles/RtMidiLib_autogen.dir/build.make
.PHONY : RtMidiLib_autogen

# Rule to build all files generated by this target.
src/RtMidiRouterLib/RtMidiWrap/libs/rtmidi/CMakeFiles/RtMidiLib_autogen.dir/build: RtMidiLib_autogen
.PHONY : src/RtMidiRouterLib/RtMidiWrap/libs/rtmidi/CMakeFiles/RtMidiLib_autogen.dir/build

src/RtMidiRouterLib/RtMidiWrap/libs/rtmidi/CMakeFiles/RtMidiLib_autogen.dir/clean:
	cd /Volumes/FAST/develop/MidiRouter/projects/RtMidiWrap/build/src/RtMidiRouterLib/RtMidiWrap/libs/rtmidi && $(CMAKE_COMMAND) -P CMakeFiles/RtMidiLib_autogen.dir/cmake_clean.cmake
.PHONY : src/RtMidiRouterLib/RtMidiWrap/libs/rtmidi/CMakeFiles/RtMidiLib_autogen.dir/clean

src/RtMidiRouterLib/RtMidiWrap/libs/rtmidi/CMakeFiles/RtMidiLib_autogen.dir/depend:
	cd /Volumes/FAST/develop/MidiRouter/projects/RtMidiWrap/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Volumes/FAST/develop/MidiRouter/projects/RtMidiWrap /Volumes/FAST/develop/MidiRouter/projects/RtMidiWrap/src/RtMidiRouterLib/RtMidiWrap/libs/rtmidi /Volumes/FAST/develop/MidiRouter/projects/RtMidiWrap/build /Volumes/FAST/develop/MidiRouter/projects/RtMidiWrap/build/src/RtMidiRouterLib/RtMidiWrap/libs/rtmidi /Volumes/FAST/develop/MidiRouter/projects/RtMidiWrap/build/src/RtMidiRouterLib/RtMidiWrap/libs/rtmidi/CMakeFiles/RtMidiLib_autogen.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/RtMidiRouterLib/RtMidiWrap/libs/rtmidi/CMakeFiles/RtMidiLib_autogen.dir/depend

