# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

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
CMAKE_SOURCE_DIR = /home/lekkkim/Desktop/repos/MainRepo/ARGoS

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/lekkkim/Desktop/repos/MainRepo/ARGoS/build

# Include any dependencies generated for this target.
include controllers/alibot/CMakeFiles/alibot.dir/depend.make

# Include the progress variables for this target.
include controllers/alibot/CMakeFiles/alibot.dir/progress.make

# Include the compile flags for this target's objects.
include controllers/alibot/CMakeFiles/alibot.dir/flags.make

controllers/alibot/CMakeFiles/alibot.dir/alibot.cpp.o: controllers/alibot/CMakeFiles/alibot.dir/flags.make
controllers/alibot/CMakeFiles/alibot.dir/alibot.cpp.o: ../controllers/alibot/alibot.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/lekkkim/Desktop/repos/MainRepo/ARGoS/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object controllers/alibot/CMakeFiles/alibot.dir/alibot.cpp.o"
	cd /home/lekkkim/Desktop/repos/MainRepo/ARGoS/build/controllers/alibot && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/alibot.dir/alibot.cpp.o -c /home/lekkkim/Desktop/repos/MainRepo/ARGoS/controllers/alibot/alibot.cpp

controllers/alibot/CMakeFiles/alibot.dir/alibot.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/alibot.dir/alibot.cpp.i"
	cd /home/lekkkim/Desktop/repos/MainRepo/ARGoS/build/controllers/alibot && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/lekkkim/Desktop/repos/MainRepo/ARGoS/controllers/alibot/alibot.cpp > CMakeFiles/alibot.dir/alibot.cpp.i

controllers/alibot/CMakeFiles/alibot.dir/alibot.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/alibot.dir/alibot.cpp.s"
	cd /home/lekkkim/Desktop/repos/MainRepo/ARGoS/build/controllers/alibot && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/lekkkim/Desktop/repos/MainRepo/ARGoS/controllers/alibot/alibot.cpp -o CMakeFiles/alibot.dir/alibot.cpp.s

controllers/alibot/CMakeFiles/alibot.dir/alibot.cpp.o.requires:

.PHONY : controllers/alibot/CMakeFiles/alibot.dir/alibot.cpp.o.requires

controllers/alibot/CMakeFiles/alibot.dir/alibot.cpp.o.provides: controllers/alibot/CMakeFiles/alibot.dir/alibot.cpp.o.requires
	$(MAKE) -f controllers/alibot/CMakeFiles/alibot.dir/build.make controllers/alibot/CMakeFiles/alibot.dir/alibot.cpp.o.provides.build
.PHONY : controllers/alibot/CMakeFiles/alibot.dir/alibot.cpp.o.provides

controllers/alibot/CMakeFiles/alibot.dir/alibot.cpp.o.provides.build: controllers/alibot/CMakeFiles/alibot.dir/alibot.cpp.o


controllers/alibot/CMakeFiles/alibot.dir/alibot_autogen/mocs_compilation.cpp.o: controllers/alibot/CMakeFiles/alibot.dir/flags.make
controllers/alibot/CMakeFiles/alibot.dir/alibot_autogen/mocs_compilation.cpp.o: controllers/alibot/alibot_autogen/mocs_compilation.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/lekkkim/Desktop/repos/MainRepo/ARGoS/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object controllers/alibot/CMakeFiles/alibot.dir/alibot_autogen/mocs_compilation.cpp.o"
	cd /home/lekkkim/Desktop/repos/MainRepo/ARGoS/build/controllers/alibot && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/alibot.dir/alibot_autogen/mocs_compilation.cpp.o -c /home/lekkkim/Desktop/repos/MainRepo/ARGoS/build/controllers/alibot/alibot_autogen/mocs_compilation.cpp

controllers/alibot/CMakeFiles/alibot.dir/alibot_autogen/mocs_compilation.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/alibot.dir/alibot_autogen/mocs_compilation.cpp.i"
	cd /home/lekkkim/Desktop/repos/MainRepo/ARGoS/build/controllers/alibot && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/lekkkim/Desktop/repos/MainRepo/ARGoS/build/controllers/alibot/alibot_autogen/mocs_compilation.cpp > CMakeFiles/alibot.dir/alibot_autogen/mocs_compilation.cpp.i

controllers/alibot/CMakeFiles/alibot.dir/alibot_autogen/mocs_compilation.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/alibot.dir/alibot_autogen/mocs_compilation.cpp.s"
	cd /home/lekkkim/Desktop/repos/MainRepo/ARGoS/build/controllers/alibot && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/lekkkim/Desktop/repos/MainRepo/ARGoS/build/controllers/alibot/alibot_autogen/mocs_compilation.cpp -o CMakeFiles/alibot.dir/alibot_autogen/mocs_compilation.cpp.s

controllers/alibot/CMakeFiles/alibot.dir/alibot_autogen/mocs_compilation.cpp.o.requires:

.PHONY : controllers/alibot/CMakeFiles/alibot.dir/alibot_autogen/mocs_compilation.cpp.o.requires

controllers/alibot/CMakeFiles/alibot.dir/alibot_autogen/mocs_compilation.cpp.o.provides: controllers/alibot/CMakeFiles/alibot.dir/alibot_autogen/mocs_compilation.cpp.o.requires
	$(MAKE) -f controllers/alibot/CMakeFiles/alibot.dir/build.make controllers/alibot/CMakeFiles/alibot.dir/alibot_autogen/mocs_compilation.cpp.o.provides.build
.PHONY : controllers/alibot/CMakeFiles/alibot.dir/alibot_autogen/mocs_compilation.cpp.o.provides

controllers/alibot/CMakeFiles/alibot.dir/alibot_autogen/mocs_compilation.cpp.o.provides.build: controllers/alibot/CMakeFiles/alibot.dir/alibot_autogen/mocs_compilation.cpp.o


# Object files for target alibot
alibot_OBJECTS = \
"CMakeFiles/alibot.dir/alibot.cpp.o" \
"CMakeFiles/alibot.dir/alibot_autogen/mocs_compilation.cpp.o"

# External object files for target alibot
alibot_EXTERNAL_OBJECTS =

controllers/alibot/libalibot.so: controllers/alibot/CMakeFiles/alibot.dir/alibot.cpp.o
controllers/alibot/libalibot.so: controllers/alibot/CMakeFiles/alibot.dir/alibot_autogen/mocs_compilation.cpp.o
controllers/alibot/libalibot.so: controllers/alibot/CMakeFiles/alibot.dir/build.make
controllers/alibot/libalibot.so: controllers/alibot/CMakeFiles/alibot.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/lekkkim/Desktop/repos/MainRepo/ARGoS/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX shared module libalibot.so"
	cd /home/lekkkim/Desktop/repos/MainRepo/ARGoS/build/controllers/alibot && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/alibot.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
controllers/alibot/CMakeFiles/alibot.dir/build: controllers/alibot/libalibot.so

.PHONY : controllers/alibot/CMakeFiles/alibot.dir/build

controllers/alibot/CMakeFiles/alibot.dir/requires: controllers/alibot/CMakeFiles/alibot.dir/alibot.cpp.o.requires
controllers/alibot/CMakeFiles/alibot.dir/requires: controllers/alibot/CMakeFiles/alibot.dir/alibot_autogen/mocs_compilation.cpp.o.requires

.PHONY : controllers/alibot/CMakeFiles/alibot.dir/requires

controllers/alibot/CMakeFiles/alibot.dir/clean:
	cd /home/lekkkim/Desktop/repos/MainRepo/ARGoS/build/controllers/alibot && $(CMAKE_COMMAND) -P CMakeFiles/alibot.dir/cmake_clean.cmake
.PHONY : controllers/alibot/CMakeFiles/alibot.dir/clean

controllers/alibot/CMakeFiles/alibot.dir/depend:
	cd /home/lekkkim/Desktop/repos/MainRepo/ARGoS/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/lekkkim/Desktop/repos/MainRepo/ARGoS /home/lekkkim/Desktop/repos/MainRepo/ARGoS/controllers/alibot /home/lekkkim/Desktop/repos/MainRepo/ARGoS/build /home/lekkkim/Desktop/repos/MainRepo/ARGoS/build/controllers/alibot /home/lekkkim/Desktop/repos/MainRepo/ARGoS/build/controllers/alibot/CMakeFiles/alibot.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : controllers/alibot/CMakeFiles/alibot.dir/depend

