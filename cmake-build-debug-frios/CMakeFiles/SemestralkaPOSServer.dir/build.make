# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.18

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
CMAKE_SOURCE_DIR = /tmp/tmp.41KBJRtAQo

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /tmp/tmp.41KBJRtAQo/cmake-build-debug-frios

# Include any dependencies generated for this target.
include CMakeFiles/SemestralkaPOSServer.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/SemestralkaPOSServer.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/SemestralkaPOSServer.dir/flags.make

CMakeFiles/SemestralkaPOSServer.dir/main.c.o: CMakeFiles/SemestralkaPOSServer.dir/flags.make
CMakeFiles/SemestralkaPOSServer.dir/main.c.o: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/tmp/tmp.41KBJRtAQo/cmake-build-debug-frios/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/SemestralkaPOSServer.dir/main.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/SemestralkaPOSServer.dir/main.c.o -c /tmp/tmp.41KBJRtAQo/main.c

CMakeFiles/SemestralkaPOSServer.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/SemestralkaPOSServer.dir/main.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /tmp/tmp.41KBJRtAQo/main.c > CMakeFiles/SemestralkaPOSServer.dir/main.c.i

CMakeFiles/SemestralkaPOSServer.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/SemestralkaPOSServer.dir/main.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /tmp/tmp.41KBJRtAQo/main.c -o CMakeFiles/SemestralkaPOSServer.dir/main.c.s

CMakeFiles/SemestralkaPOSServer.dir/pos_sockets/active_socket.c.o: CMakeFiles/SemestralkaPOSServer.dir/flags.make
CMakeFiles/SemestralkaPOSServer.dir/pos_sockets/active_socket.c.o: ../pos_sockets/active_socket.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/tmp/tmp.41KBJRtAQo/cmake-build-debug-frios/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/SemestralkaPOSServer.dir/pos_sockets/active_socket.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/SemestralkaPOSServer.dir/pos_sockets/active_socket.c.o -c /tmp/tmp.41KBJRtAQo/pos_sockets/active_socket.c

CMakeFiles/SemestralkaPOSServer.dir/pos_sockets/active_socket.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/SemestralkaPOSServer.dir/pos_sockets/active_socket.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /tmp/tmp.41KBJRtAQo/pos_sockets/active_socket.c > CMakeFiles/SemestralkaPOSServer.dir/pos_sockets/active_socket.c.i

CMakeFiles/SemestralkaPOSServer.dir/pos_sockets/active_socket.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/SemestralkaPOSServer.dir/pos_sockets/active_socket.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /tmp/tmp.41KBJRtAQo/pos_sockets/active_socket.c -o CMakeFiles/SemestralkaPOSServer.dir/pos_sockets/active_socket.c.s

CMakeFiles/SemestralkaPOSServer.dir/pos_sockets/char_buffer.c.o: CMakeFiles/SemestralkaPOSServer.dir/flags.make
CMakeFiles/SemestralkaPOSServer.dir/pos_sockets/char_buffer.c.o: ../pos_sockets/char_buffer.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/tmp/tmp.41KBJRtAQo/cmake-build-debug-frios/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/SemestralkaPOSServer.dir/pos_sockets/char_buffer.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/SemestralkaPOSServer.dir/pos_sockets/char_buffer.c.o -c /tmp/tmp.41KBJRtAQo/pos_sockets/char_buffer.c

CMakeFiles/SemestralkaPOSServer.dir/pos_sockets/char_buffer.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/SemestralkaPOSServer.dir/pos_sockets/char_buffer.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /tmp/tmp.41KBJRtAQo/pos_sockets/char_buffer.c > CMakeFiles/SemestralkaPOSServer.dir/pos_sockets/char_buffer.c.i

CMakeFiles/SemestralkaPOSServer.dir/pos_sockets/char_buffer.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/SemestralkaPOSServer.dir/pos_sockets/char_buffer.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /tmp/tmp.41KBJRtAQo/pos_sockets/char_buffer.c -o CMakeFiles/SemestralkaPOSServer.dir/pos_sockets/char_buffer.c.s

CMakeFiles/SemestralkaPOSServer.dir/pos_sockets/passive_socket.c.o: CMakeFiles/SemestralkaPOSServer.dir/flags.make
CMakeFiles/SemestralkaPOSServer.dir/pos_sockets/passive_socket.c.o: ../pos_sockets/passive_socket.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/tmp/tmp.41KBJRtAQo/cmake-build-debug-frios/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object CMakeFiles/SemestralkaPOSServer.dir/pos_sockets/passive_socket.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/SemestralkaPOSServer.dir/pos_sockets/passive_socket.c.o -c /tmp/tmp.41KBJRtAQo/pos_sockets/passive_socket.c

CMakeFiles/SemestralkaPOSServer.dir/pos_sockets/passive_socket.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/SemestralkaPOSServer.dir/pos_sockets/passive_socket.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /tmp/tmp.41KBJRtAQo/pos_sockets/passive_socket.c > CMakeFiles/SemestralkaPOSServer.dir/pos_sockets/passive_socket.c.i

CMakeFiles/SemestralkaPOSServer.dir/pos_sockets/passive_socket.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/SemestralkaPOSServer.dir/pos_sockets/passive_socket.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /tmp/tmp.41KBJRtAQo/pos_sockets/passive_socket.c -o CMakeFiles/SemestralkaPOSServer.dir/pos_sockets/passive_socket.c.s

# Object files for target SemestralkaPOSServer
SemestralkaPOSServer_OBJECTS = \
"CMakeFiles/SemestralkaPOSServer.dir/main.c.o" \
"CMakeFiles/SemestralkaPOSServer.dir/pos_sockets/active_socket.c.o" \
"CMakeFiles/SemestralkaPOSServer.dir/pos_sockets/char_buffer.c.o" \
"CMakeFiles/SemestralkaPOSServer.dir/pos_sockets/passive_socket.c.o"

# External object files for target SemestralkaPOSServer
SemestralkaPOSServer_EXTERNAL_OBJECTS =

SemestralkaPOSServer: CMakeFiles/SemestralkaPOSServer.dir/main.c.o
SemestralkaPOSServer: CMakeFiles/SemestralkaPOSServer.dir/pos_sockets/active_socket.c.o
SemestralkaPOSServer: CMakeFiles/SemestralkaPOSServer.dir/pos_sockets/char_buffer.c.o
SemestralkaPOSServer: CMakeFiles/SemestralkaPOSServer.dir/pos_sockets/passive_socket.c.o
SemestralkaPOSServer: CMakeFiles/SemestralkaPOSServer.dir/build.make
SemestralkaPOSServer: CMakeFiles/SemestralkaPOSServer.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/tmp/tmp.41KBJRtAQo/cmake-build-debug-frios/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking C executable SemestralkaPOSServer"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/SemestralkaPOSServer.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/SemestralkaPOSServer.dir/build: SemestralkaPOSServer

.PHONY : CMakeFiles/SemestralkaPOSServer.dir/build

CMakeFiles/SemestralkaPOSServer.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/SemestralkaPOSServer.dir/cmake_clean.cmake
.PHONY : CMakeFiles/SemestralkaPOSServer.dir/clean

CMakeFiles/SemestralkaPOSServer.dir/depend:
	cd /tmp/tmp.41KBJRtAQo/cmake-build-debug-frios && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /tmp/tmp.41KBJRtAQo /tmp/tmp.41KBJRtAQo /tmp/tmp.41KBJRtAQo/cmake-build-debug-frios /tmp/tmp.41KBJRtAQo/cmake-build-debug-frios /tmp/tmp.41KBJRtAQo/cmake-build-debug-frios/CMakeFiles/SemestralkaPOSServer.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/SemestralkaPOSServer.dir/depend
