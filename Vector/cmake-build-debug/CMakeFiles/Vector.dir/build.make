# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.8

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
CMAKE_COMMAND = /home/tianbao/文档/clion-2017.2.2/bin/cmake/bin/cmake

# The command to remove a file.
RM = /home/tianbao/文档/clion-2017.2.2/bin/cmake/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/tianbao/CLionProjects/Vector

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/tianbao/CLionProjects/Vector/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/Vector.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Vector.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Vector.dir/flags.make

CMakeFiles/Vector.dir/main.cpp.o: CMakeFiles/Vector.dir/flags.make
CMakeFiles/Vector.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tianbao/CLionProjects/Vector/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Vector.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Vector.dir/main.cpp.o -c /home/tianbao/CLionProjects/Vector/main.cpp

CMakeFiles/Vector.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Vector.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/tianbao/CLionProjects/Vector/main.cpp > CMakeFiles/Vector.dir/main.cpp.i

CMakeFiles/Vector.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Vector.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/tianbao/CLionProjects/Vector/main.cpp -o CMakeFiles/Vector.dir/main.cpp.s

CMakeFiles/Vector.dir/main.cpp.o.requires:

.PHONY : CMakeFiles/Vector.dir/main.cpp.o.requires

CMakeFiles/Vector.dir/main.cpp.o.provides: CMakeFiles/Vector.dir/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/Vector.dir/build.make CMakeFiles/Vector.dir/main.cpp.o.provides.build
.PHONY : CMakeFiles/Vector.dir/main.cpp.o.provides

CMakeFiles/Vector.dir/main.cpp.o.provides.build: CMakeFiles/Vector.dir/main.cpp.o


# Object files for target Vector
Vector_OBJECTS = \
"CMakeFiles/Vector.dir/main.cpp.o"

# External object files for target Vector
Vector_EXTERNAL_OBJECTS =

Vector: CMakeFiles/Vector.dir/main.cpp.o
Vector: CMakeFiles/Vector.dir/build.make
Vector: CMakeFiles/Vector.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/tianbao/CLionProjects/Vector/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable Vector"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Vector.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Vector.dir/build: Vector

.PHONY : CMakeFiles/Vector.dir/build

CMakeFiles/Vector.dir/requires: CMakeFiles/Vector.dir/main.cpp.o.requires

.PHONY : CMakeFiles/Vector.dir/requires

CMakeFiles/Vector.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Vector.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Vector.dir/clean

CMakeFiles/Vector.dir/depend:
	cd /home/tianbao/CLionProjects/Vector/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/tianbao/CLionProjects/Vector /home/tianbao/CLionProjects/Vector /home/tianbao/CLionProjects/Vector/cmake-build-debug /home/tianbao/CLionProjects/Vector/cmake-build-debug /home/tianbao/CLionProjects/Vector/cmake-build-debug/CMakeFiles/Vector.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Vector.dir/depend

