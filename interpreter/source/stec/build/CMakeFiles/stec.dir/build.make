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
CMAKE_SOURCE_DIR = /home/leopoldkucinski/Dokumenty/stec

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/leopoldkucinski/Dokumenty/stec/build

# Include any dependencies generated for this target.
include CMakeFiles/stec.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/stec.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/stec.dir/flags.make

CMakeFiles/stec.dir/main.cpp.o: CMakeFiles/stec.dir/flags.make
CMakeFiles/stec.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/leopoldkucinski/Dokumenty/stec/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/stec.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/stec.dir/main.cpp.o -c /home/leopoldkucinski/Dokumenty/stec/main.cpp

CMakeFiles/stec.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/stec.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/leopoldkucinski/Dokumenty/stec/main.cpp > CMakeFiles/stec.dir/main.cpp.i

CMakeFiles/stec.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/stec.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/leopoldkucinski/Dokumenty/stec/main.cpp -o CMakeFiles/stec.dir/main.cpp.s

# Object files for target stec
stec_OBJECTS = \
"CMakeFiles/stec.dir/main.cpp.o"

# External object files for target stec
stec_EXTERNAL_OBJECTS =

stec: CMakeFiles/stec.dir/main.cpp.o
stec: CMakeFiles/stec.dir/build.make
stec: CMakeFiles/stec.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/leopoldkucinski/Dokumenty/stec/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable stec"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/stec.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/stec.dir/build: stec

.PHONY : CMakeFiles/stec.dir/build

CMakeFiles/stec.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/stec.dir/cmake_clean.cmake
.PHONY : CMakeFiles/stec.dir/clean

CMakeFiles/stec.dir/depend:
	cd /home/leopoldkucinski/Dokumenty/stec/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/leopoldkucinski/Dokumenty/stec /home/leopoldkucinski/Dokumenty/stec /home/leopoldkucinski/Dokumenty/stec/build /home/leopoldkucinski/Dokumenty/stec/build /home/leopoldkucinski/Dokumenty/stec/build/CMakeFiles/stec.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/stec.dir/depend

