# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.15

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
CMAKE_COMMAND = /opt/clion-2019.3.4/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /opt/clion-2019.3.4/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/stran/Documents/raytracing

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/stran/Documents/raytracing/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/raytracing.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/raytracing.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/raytracing.dir/flags.make

CMakeFiles/raytracing.dir/main.cpp.o: CMakeFiles/raytracing.dir/flags.make
CMakeFiles/raytracing.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/stran/Documents/raytracing/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/raytracing.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/raytracing.dir/main.cpp.o -c /home/stran/Documents/raytracing/main.cpp

CMakeFiles/raytracing.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/raytracing.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/stran/Documents/raytracing/main.cpp > CMakeFiles/raytracing.dir/main.cpp.i

CMakeFiles/raytracing.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/raytracing.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/stran/Documents/raytracing/main.cpp -o CMakeFiles/raytracing.dir/main.cpp.s

CMakeFiles/raytracing.dir/vec3.cpp.o: CMakeFiles/raytracing.dir/flags.make
CMakeFiles/raytracing.dir/vec3.cpp.o: ../vec3.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/stran/Documents/raytracing/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/raytracing.dir/vec3.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/raytracing.dir/vec3.cpp.o -c /home/stran/Documents/raytracing/vec3.cpp

CMakeFiles/raytracing.dir/vec3.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/raytracing.dir/vec3.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/stran/Documents/raytracing/vec3.cpp > CMakeFiles/raytracing.dir/vec3.cpp.i

CMakeFiles/raytracing.dir/vec3.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/raytracing.dir/vec3.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/stran/Documents/raytracing/vec3.cpp -o CMakeFiles/raytracing.dir/vec3.cpp.s

# Object files for target raytracing
raytracing_OBJECTS = \
"CMakeFiles/raytracing.dir/main.cpp.o" \
"CMakeFiles/raytracing.dir/vec3.cpp.o"

# External object files for target raytracing
raytracing_EXTERNAL_OBJECTS =

raytracing: CMakeFiles/raytracing.dir/main.cpp.o
raytracing: CMakeFiles/raytracing.dir/vec3.cpp.o
raytracing: CMakeFiles/raytracing.dir/build.make
raytracing: CMakeFiles/raytracing.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/stran/Documents/raytracing/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable raytracing"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/raytracing.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/raytracing.dir/build: raytracing

.PHONY : CMakeFiles/raytracing.dir/build

CMakeFiles/raytracing.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/raytracing.dir/cmake_clean.cmake
.PHONY : CMakeFiles/raytracing.dir/clean

CMakeFiles/raytracing.dir/depend:
	cd /home/stran/Documents/raytracing/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/stran/Documents/raytracing /home/stran/Documents/raytracing /home/stran/Documents/raytracing/cmake-build-debug /home/stran/Documents/raytracing/cmake-build-debug /home/stran/Documents/raytracing/cmake-build-debug/CMakeFiles/raytracing.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/raytracing.dir/depend

