# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
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
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /mnt/c/Users/Fabio/CLionProjects/cBuffer

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /mnt/c/Users/Fabio/CLionProjects/cBuffer/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/cBuffer.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/cBuffer.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/cBuffer.dir/flags.make

CMakeFiles/cBuffer.dir/main.cpp.o: CMakeFiles/cBuffer.dir/flags.make
CMakeFiles/cBuffer.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/Fabio/CLionProjects/cBuffer/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/cBuffer.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/cBuffer.dir/main.cpp.o -c /mnt/c/Users/Fabio/CLionProjects/cBuffer/main.cpp

CMakeFiles/cBuffer.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/cBuffer.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/Users/Fabio/CLionProjects/cBuffer/main.cpp > CMakeFiles/cBuffer.dir/main.cpp.i

CMakeFiles/cBuffer.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/cBuffer.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/Users/Fabio/CLionProjects/cBuffer/main.cpp -o CMakeFiles/cBuffer.dir/main.cpp.s

CMakeFiles/cBuffer.dir/exeptionBuffer.cpp.o: CMakeFiles/cBuffer.dir/flags.make
CMakeFiles/cBuffer.dir/exeptionBuffer.cpp.o: exeptionBuffer.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/Fabio/CLionProjects/cBuffer/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/cBuffer.dir/exeptionBuffer.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/cBuffer.dir/exeptionBuffer.cpp.o -c /mnt/c/Users/Fabio/CLionProjects/cBuffer/cmake-build-debug/exeptionBuffer.cpp

CMakeFiles/cBuffer.dir/exeptionBuffer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/cBuffer.dir/exeptionBuffer.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/Users/Fabio/CLionProjects/cBuffer/cmake-build-debug/exeptionBuffer.cpp > CMakeFiles/cBuffer.dir/exeptionBuffer.cpp.i

CMakeFiles/cBuffer.dir/exeptionBuffer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/cBuffer.dir/exeptionBuffer.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/Users/Fabio/CLionProjects/cBuffer/cmake-build-debug/exeptionBuffer.cpp -o CMakeFiles/cBuffer.dir/exeptionBuffer.cpp.s

# Object files for target cBuffer
cBuffer_OBJECTS = \
"CMakeFiles/cBuffer.dir/main.cpp.o" \
"CMakeFiles/cBuffer.dir/exeptionBuffer.cpp.o"

# External object files for target cBuffer
cBuffer_EXTERNAL_OBJECTS =

cBuffer: CMakeFiles/cBuffer.dir/main.cpp.o
cBuffer: CMakeFiles/cBuffer.dir/exeptionBuffer.cpp.o
cBuffer: CMakeFiles/cBuffer.dir/build.make
cBuffer: CMakeFiles/cBuffer.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/mnt/c/Users/Fabio/CLionProjects/cBuffer/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable cBuffer"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/cBuffer.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/cBuffer.dir/build: cBuffer

.PHONY : CMakeFiles/cBuffer.dir/build

CMakeFiles/cBuffer.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/cBuffer.dir/cmake_clean.cmake
.PHONY : CMakeFiles/cBuffer.dir/clean

CMakeFiles/cBuffer.dir/depend:
	cd /mnt/c/Users/Fabio/CLionProjects/cBuffer/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/c/Users/Fabio/CLionProjects/cBuffer /mnt/c/Users/Fabio/CLionProjects/cBuffer /mnt/c/Users/Fabio/CLionProjects/cBuffer/cmake-build-debug /mnt/c/Users/Fabio/CLionProjects/cBuffer/cmake-build-debug /mnt/c/Users/Fabio/CLionProjects/cBuffer/cmake-build-debug/CMakeFiles/cBuffer.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/cBuffer.dir/depend

