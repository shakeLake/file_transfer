# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/mark/Desktop/data/geass/csc

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/mark/Desktop/data/geass/csc

# Include any dependencies generated for this target.
include server/CMakeFiles/serverLib.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include server/CMakeFiles/serverLib.dir/compiler_depend.make

# Include the progress variables for this target.
include server/CMakeFiles/serverLib.dir/progress.make

# Include the compile flags for this target's objects.
include server/CMakeFiles/serverLib.dir/flags.make

server/CMakeFiles/serverLib.dir/server.cpp.o: server/CMakeFiles/serverLib.dir/flags.make
server/CMakeFiles/serverLib.dir/server.cpp.o: server/server.cpp
server/CMakeFiles/serverLib.dir/server.cpp.o: server/CMakeFiles/serverLib.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/mark/Desktop/data/geass/csc/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object server/CMakeFiles/serverLib.dir/server.cpp.o"
	cd /home/mark/Desktop/data/geass/csc/server && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT server/CMakeFiles/serverLib.dir/server.cpp.o -MF CMakeFiles/serverLib.dir/server.cpp.o.d -o CMakeFiles/serverLib.dir/server.cpp.o -c /home/mark/Desktop/data/geass/csc/server/server.cpp

server/CMakeFiles/serverLib.dir/server.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/serverLib.dir/server.cpp.i"
	cd /home/mark/Desktop/data/geass/csc/server && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/mark/Desktop/data/geass/csc/server/server.cpp > CMakeFiles/serverLib.dir/server.cpp.i

server/CMakeFiles/serverLib.dir/server.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/serverLib.dir/server.cpp.s"
	cd /home/mark/Desktop/data/geass/csc/server && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/mark/Desktop/data/geass/csc/server/server.cpp -o CMakeFiles/serverLib.dir/server.cpp.s

server/CMakeFiles/serverLib.dir/session.cpp.o: server/CMakeFiles/serverLib.dir/flags.make
server/CMakeFiles/serverLib.dir/session.cpp.o: server/session.cpp
server/CMakeFiles/serverLib.dir/session.cpp.o: server/CMakeFiles/serverLib.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/mark/Desktop/data/geass/csc/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object server/CMakeFiles/serverLib.dir/session.cpp.o"
	cd /home/mark/Desktop/data/geass/csc/server && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT server/CMakeFiles/serverLib.dir/session.cpp.o -MF CMakeFiles/serverLib.dir/session.cpp.o.d -o CMakeFiles/serverLib.dir/session.cpp.o -c /home/mark/Desktop/data/geass/csc/server/session.cpp

server/CMakeFiles/serverLib.dir/session.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/serverLib.dir/session.cpp.i"
	cd /home/mark/Desktop/data/geass/csc/server && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/mark/Desktop/data/geass/csc/server/session.cpp > CMakeFiles/serverLib.dir/session.cpp.i

server/CMakeFiles/serverLib.dir/session.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/serverLib.dir/session.cpp.s"
	cd /home/mark/Desktop/data/geass/csc/server && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/mark/Desktop/data/geass/csc/server/session.cpp -o CMakeFiles/serverLib.dir/session.cpp.s

# Object files for target serverLib
serverLib_OBJECTS = \
"CMakeFiles/serverLib.dir/server.cpp.o" \
"CMakeFiles/serverLib.dir/session.cpp.o"

# External object files for target serverLib
serverLib_EXTERNAL_OBJECTS =

server/libserverLib.a: server/CMakeFiles/serverLib.dir/server.cpp.o
server/libserverLib.a: server/CMakeFiles/serverLib.dir/session.cpp.o
server/libserverLib.a: server/CMakeFiles/serverLib.dir/build.make
server/libserverLib.a: server/CMakeFiles/serverLib.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/mark/Desktop/data/geass/csc/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX static library libserverLib.a"
	cd /home/mark/Desktop/data/geass/csc/server && $(CMAKE_COMMAND) -P CMakeFiles/serverLib.dir/cmake_clean_target.cmake
	cd /home/mark/Desktop/data/geass/csc/server && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/serverLib.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
server/CMakeFiles/serverLib.dir/build: server/libserverLib.a
.PHONY : server/CMakeFiles/serverLib.dir/build

server/CMakeFiles/serverLib.dir/clean:
	cd /home/mark/Desktop/data/geass/csc/server && $(CMAKE_COMMAND) -P CMakeFiles/serverLib.dir/cmake_clean.cmake
.PHONY : server/CMakeFiles/serverLib.dir/clean

server/CMakeFiles/serverLib.dir/depend:
	cd /home/mark/Desktop/data/geass/csc && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/mark/Desktop/data/geass/csc /home/mark/Desktop/data/geass/csc/server /home/mark/Desktop/data/geass/csc /home/mark/Desktop/data/geass/csc/server /home/mark/Desktop/data/geass/csc/server/CMakeFiles/serverLib.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : server/CMakeFiles/serverLib.dir/depend

