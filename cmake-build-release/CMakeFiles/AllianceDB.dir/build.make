# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.9

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
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/shuhaozhang/ClionProjects/AllianceDB

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/shuhaozhang/ClionProjects/AllianceDB/cmake-build-release

# Include any dependencies generated for this target.
include CMakeFiles/AllianceDB.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/AllianceDB.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/AllianceDB.dir/flags.make

CMakeFiles/AllianceDB.dir/main.cpp.o: CMakeFiles/AllianceDB.dir/flags.make
CMakeFiles/AllianceDB.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/shuhaozhang/ClionProjects/AllianceDB/cmake-build-release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/AllianceDB.dir/main.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/AllianceDB.dir/main.cpp.o -c /Users/shuhaozhang/ClionProjects/AllianceDB/main.cpp

CMakeFiles/AllianceDB.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/AllianceDB.dir/main.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/shuhaozhang/ClionProjects/AllianceDB/main.cpp > CMakeFiles/AllianceDB.dir/main.cpp.i

CMakeFiles/AllianceDB.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/AllianceDB.dir/main.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/shuhaozhang/ClionProjects/AllianceDB/main.cpp -o CMakeFiles/AllianceDB.dir/main.cpp.s

CMakeFiles/AllianceDB.dir/main.cpp.o.requires:

.PHONY : CMakeFiles/AllianceDB.dir/main.cpp.o.requires

CMakeFiles/AllianceDB.dir/main.cpp.o.provides: CMakeFiles/AllianceDB.dir/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/AllianceDB.dir/build.make CMakeFiles/AllianceDB.dir/main.cpp.o.provides.build
.PHONY : CMakeFiles/AllianceDB.dir/main.cpp.o.provides

CMakeFiles/AllianceDB.dir/main.cpp.o.provides.build: CMakeFiles/AllianceDB.dir/main.cpp.o


# Object files for target AllianceDB
AllianceDB_OBJECTS = \
"CMakeFiles/AllianceDB.dir/main.cpp.o"

# External object files for target AllianceDB
AllianceDB_EXTERNAL_OBJECTS =

AllianceDB: CMakeFiles/AllianceDB.dir/main.cpp.o
AllianceDB: CMakeFiles/AllianceDB.dir/build.make
AllianceDB: CMakeFiles/AllianceDB.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/shuhaozhang/ClionProjects/AllianceDB/cmake-build-release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable AllianceDB"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/AllianceDB.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/AllianceDB.dir/build: AllianceDB

.PHONY : CMakeFiles/AllianceDB.dir/build

CMakeFiles/AllianceDB.dir/requires: CMakeFiles/AllianceDB.dir/main.cpp.o.requires

.PHONY : CMakeFiles/AllianceDB.dir/requires

CMakeFiles/AllianceDB.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/AllianceDB.dir/cmake_clean.cmake
.PHONY : CMakeFiles/AllianceDB.dir/clean

CMakeFiles/AllianceDB.dir/depend:
	cd /Users/shuhaozhang/ClionProjects/AllianceDB/cmake-build-release && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/shuhaozhang/ClionProjects/AllianceDB /Users/shuhaozhang/ClionProjects/AllianceDB /Users/shuhaozhang/ClionProjects/AllianceDB/cmake-build-release /Users/shuhaozhang/ClionProjects/AllianceDB/cmake-build-release /Users/shuhaozhang/ClionProjects/AllianceDB/cmake-build-release/CMakeFiles/AllianceDB.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/AllianceDB.dir/depend

