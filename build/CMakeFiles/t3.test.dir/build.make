# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.29

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
CMAKE_SOURCE_DIR = /home/gon/Developer/Utils

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/gon/Developer/Utils/build

# Include any dependencies generated for this target.
include CMakeFiles/t3.test.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/t3.test.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/t3.test.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/t3.test.dir/flags.make

CMakeFiles/t3.test.dir/tests/t3.c.o: CMakeFiles/t3.test.dir/flags.make
CMakeFiles/t3.test.dir/tests/t3.c.o: /home/gon/Developer/Utils/tests/t3.c
CMakeFiles/t3.test.dir/tests/t3.c.o: CMakeFiles/t3.test.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/gon/Developer/Utils/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/t3.test.dir/tests/t3.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/t3.test.dir/tests/t3.c.o -MF CMakeFiles/t3.test.dir/tests/t3.c.o.d -o CMakeFiles/t3.test.dir/tests/t3.c.o -c /home/gon/Developer/Utils/tests/t3.c

CMakeFiles/t3.test.dir/tests/t3.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/t3.test.dir/tests/t3.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/gon/Developer/Utils/tests/t3.c > CMakeFiles/t3.test.dir/tests/t3.c.i

CMakeFiles/t3.test.dir/tests/t3.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/t3.test.dir/tests/t3.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/gon/Developer/Utils/tests/t3.c -o CMakeFiles/t3.test.dir/tests/t3.c.s

CMakeFiles/t3.test.dir/Utils/utils.c.o: CMakeFiles/t3.test.dir/flags.make
CMakeFiles/t3.test.dir/Utils/utils.c.o: /home/gon/Developer/Utils/Utils/utils.c
CMakeFiles/t3.test.dir/Utils/utils.c.o: CMakeFiles/t3.test.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/gon/Developer/Utils/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/t3.test.dir/Utils/utils.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/t3.test.dir/Utils/utils.c.o -MF CMakeFiles/t3.test.dir/Utils/utils.c.o.d -o CMakeFiles/t3.test.dir/Utils/utils.c.o -c /home/gon/Developer/Utils/Utils/utils.c

CMakeFiles/t3.test.dir/Utils/utils.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/t3.test.dir/Utils/utils.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/gon/Developer/Utils/Utils/utils.c > CMakeFiles/t3.test.dir/Utils/utils.c.i

CMakeFiles/t3.test.dir/Utils/utils.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/t3.test.dir/Utils/utils.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/gon/Developer/Utils/Utils/utils.c -o CMakeFiles/t3.test.dir/Utils/utils.c.s

# Object files for target t3.test
t3_test_OBJECTS = \
"CMakeFiles/t3.test.dir/tests/t3.c.o" \
"CMakeFiles/t3.test.dir/Utils/utils.c.o"

# External object files for target t3.test
t3_test_EXTERNAL_OBJECTS =

t3.test: CMakeFiles/t3.test.dir/tests/t3.c.o
t3.test: CMakeFiles/t3.test.dir/Utils/utils.c.o
t3.test: CMakeFiles/t3.test.dir/build.make
t3.test: CMakeFiles/t3.test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/gon/Developer/Utils/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C executable t3.test"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/t3.test.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/t3.test.dir/build: t3.test
.PHONY : CMakeFiles/t3.test.dir/build

CMakeFiles/t3.test.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/t3.test.dir/cmake_clean.cmake
.PHONY : CMakeFiles/t3.test.dir/clean

CMakeFiles/t3.test.dir/depend:
	cd /home/gon/Developer/Utils/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/gon/Developer/Utils /home/gon/Developer/Utils /home/gon/Developer/Utils/build /home/gon/Developer/Utils/build /home/gon/Developer/Utils/build/CMakeFiles/t3.test.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/t3.test.dir/depend
