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
CMAKE_SOURCE_DIR = /home/dtchorni/Documents/New_Raytracer/shared/glfw-3.1.1

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/dtchorni/Documents/New_Raytracer/shared/glfw-3.1.1/build

# Include any dependencies generated for this target.
include tests/CMakeFiles/sharing.dir/depend.make

# Include the progress variables for this target.
include tests/CMakeFiles/sharing.dir/progress.make

# Include the compile flags for this target's objects.
include tests/CMakeFiles/sharing.dir/flags.make

tests/CMakeFiles/sharing.dir/sharing.c.o: tests/CMakeFiles/sharing.dir/flags.make
tests/CMakeFiles/sharing.dir/sharing.c.o: ../tests/sharing.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dtchorni/Documents/New_Raytracer/shared/glfw-3.1.1/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object tests/CMakeFiles/sharing.dir/sharing.c.o"
	cd /home/dtchorni/Documents/New_Raytracer/shared/glfw-3.1.1/build/tests && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/sharing.dir/sharing.c.o   -c /home/dtchorni/Documents/New_Raytracer/shared/glfw-3.1.1/tests/sharing.c

tests/CMakeFiles/sharing.dir/sharing.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/sharing.dir/sharing.c.i"
	cd /home/dtchorni/Documents/New_Raytracer/shared/glfw-3.1.1/build/tests && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/dtchorni/Documents/New_Raytracer/shared/glfw-3.1.1/tests/sharing.c > CMakeFiles/sharing.dir/sharing.c.i

tests/CMakeFiles/sharing.dir/sharing.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/sharing.dir/sharing.c.s"
	cd /home/dtchorni/Documents/New_Raytracer/shared/glfw-3.1.1/build/tests && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/dtchorni/Documents/New_Raytracer/shared/glfw-3.1.1/tests/sharing.c -o CMakeFiles/sharing.dir/sharing.c.s

tests/CMakeFiles/sharing.dir/sharing.c.o.requires:

.PHONY : tests/CMakeFiles/sharing.dir/sharing.c.o.requires

tests/CMakeFiles/sharing.dir/sharing.c.o.provides: tests/CMakeFiles/sharing.dir/sharing.c.o.requires
	$(MAKE) -f tests/CMakeFiles/sharing.dir/build.make tests/CMakeFiles/sharing.dir/sharing.c.o.provides.build
.PHONY : tests/CMakeFiles/sharing.dir/sharing.c.o.provides

tests/CMakeFiles/sharing.dir/sharing.c.o.provides.build: tests/CMakeFiles/sharing.dir/sharing.c.o


# Object files for target sharing
sharing_OBJECTS = \
"CMakeFiles/sharing.dir/sharing.c.o"

# External object files for target sharing
sharing_EXTERNAL_OBJECTS =

tests/sharing: tests/CMakeFiles/sharing.dir/sharing.c.o
tests/sharing: tests/CMakeFiles/sharing.dir/build.make
tests/sharing: src/libglfw3.a
tests/sharing: /usr/lib/x86_64-linux-gnu/libX11.so
tests/sharing: /usr/lib/x86_64-linux-gnu/libXrandr.so
tests/sharing: /usr/lib/x86_64-linux-gnu/libXinerama.so
tests/sharing: /usr/lib/x86_64-linux-gnu/libXi.so
tests/sharing: /usr/lib/x86_64-linux-gnu/libXxf86vm.so
tests/sharing: /usr/lib/x86_64-linux-gnu/librt.so
tests/sharing: /usr/lib/x86_64-linux-gnu/libm.so
tests/sharing: /usr/lib/x86_64-linux-gnu/libXcursor.so
tests/sharing: /usr/lib/x86_64-linux-gnu/libGL.so
tests/sharing: tests/CMakeFiles/sharing.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/dtchorni/Documents/New_Raytracer/shared/glfw-3.1.1/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable sharing"
	cd /home/dtchorni/Documents/New_Raytracer/shared/glfw-3.1.1/build/tests && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/sharing.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
tests/CMakeFiles/sharing.dir/build: tests/sharing

.PHONY : tests/CMakeFiles/sharing.dir/build

tests/CMakeFiles/sharing.dir/requires: tests/CMakeFiles/sharing.dir/sharing.c.o.requires

.PHONY : tests/CMakeFiles/sharing.dir/requires

tests/CMakeFiles/sharing.dir/clean:
	cd /home/dtchorni/Documents/New_Raytracer/shared/glfw-3.1.1/build/tests && $(CMAKE_COMMAND) -P CMakeFiles/sharing.dir/cmake_clean.cmake
.PHONY : tests/CMakeFiles/sharing.dir/clean

tests/CMakeFiles/sharing.dir/depend:
	cd /home/dtchorni/Documents/New_Raytracer/shared/glfw-3.1.1/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/dtchorni/Documents/New_Raytracer/shared/glfw-3.1.1 /home/dtchorni/Documents/New_Raytracer/shared/glfw-3.1.1/tests /home/dtchorni/Documents/New_Raytracer/shared/glfw-3.1.1/build /home/dtchorni/Documents/New_Raytracer/shared/glfw-3.1.1/build/tests /home/dtchorni/Documents/New_Raytracer/shared/glfw-3.1.1/build/tests/CMakeFiles/sharing.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : tests/CMakeFiles/sharing.dir/depend

