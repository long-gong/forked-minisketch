# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.14

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
CMAKE_COMMAND = /snap/clion/82/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /snap/clion/82/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Data/GitHub/forked-minisketch

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Data/GitHub/forked-minisketch/cmake-build-vcpkg

# Include any dependencies generated for this target.
include test/CMakeFiles/minisketch_test.dir/depend.make

# Include the progress variables for this target.
include test/CMakeFiles/minisketch_test.dir/progress.make

# Include the compile flags for this target's objects.
include test/CMakeFiles/minisketch_test.dir/flags.make

test/CMakeFiles/minisketch_test.dir/minisketch_test.cpp.o: test/CMakeFiles/minisketch_test.dir/flags.make
test/CMakeFiles/minisketch_test.dir/minisketch_test.cpp.o: ../test/minisketch_test.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Data/GitHub/forked-minisketch/cmake-build-vcpkg/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object test/CMakeFiles/minisketch_test.dir/minisketch_test.cpp.o"
	cd /Data/GitHub/forked-minisketch/cmake-build-vcpkg/test && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/minisketch_test.dir/minisketch_test.cpp.o -c /Data/GitHub/forked-minisketch/test/minisketch_test.cpp

test/CMakeFiles/minisketch_test.dir/minisketch_test.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/minisketch_test.dir/minisketch_test.cpp.i"
	cd /Data/GitHub/forked-minisketch/cmake-build-vcpkg/test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Data/GitHub/forked-minisketch/test/minisketch_test.cpp > CMakeFiles/minisketch_test.dir/minisketch_test.cpp.i

test/CMakeFiles/minisketch_test.dir/minisketch_test.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/minisketch_test.dir/minisketch_test.cpp.s"
	cd /Data/GitHub/forked-minisketch/cmake-build-vcpkg/test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Data/GitHub/forked-minisketch/test/minisketch_test.cpp -o CMakeFiles/minisketch_test.dir/minisketch_test.cpp.s

# Object files for target minisketch_test
minisketch_test_OBJECTS = \
"CMakeFiles/minisketch_test.dir/minisketch_test.cpp.o"

# External object files for target minisketch_test
minisketch_test_EXTERNAL_OBJECTS =

test/minisketch_test: test/CMakeFiles/minisketch_test.dir/minisketch_test.cpp.o
test/minisketch_test: test/CMakeFiles/minisketch_test.dir/build.make
test/minisketch_test: libminisketch.a
test/minisketch_test: /usr/local/vcpkg/installed/x64-linux/debug/lib/libgtestd.a
test/minisketch_test: /usr/local/vcpkg/installed/x64-linux/debug/lib/manual-link/libgtest_maind.a
test/minisketch_test: /usr/local/vcpkg/installed/x64-linux/lib/libgmock.a
test/minisketch_test: /usr/local/vcpkg/installed/x64-linux/lib/libfmt.a
test/minisketch_test: /usr/local/vcpkg/installed/x64-linux/debug/lib/libgtestd.a
test/minisketch_test: test/CMakeFiles/minisketch_test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Data/GitHub/forked-minisketch/cmake-build-vcpkg/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable minisketch_test"
	cd /Data/GitHub/forked-minisketch/cmake-build-vcpkg/test && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/minisketch_test.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
test/CMakeFiles/minisketch_test.dir/build: test/minisketch_test

.PHONY : test/CMakeFiles/minisketch_test.dir/build

test/CMakeFiles/minisketch_test.dir/clean:
	cd /Data/GitHub/forked-minisketch/cmake-build-vcpkg/test && $(CMAKE_COMMAND) -P CMakeFiles/minisketch_test.dir/cmake_clean.cmake
.PHONY : test/CMakeFiles/minisketch_test.dir/clean

test/CMakeFiles/minisketch_test.dir/depend:
	cd /Data/GitHub/forked-minisketch/cmake-build-vcpkg && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Data/GitHub/forked-minisketch /Data/GitHub/forked-minisketch/test /Data/GitHub/forked-minisketch/cmake-build-vcpkg /Data/GitHub/forked-minisketch/cmake-build-vcpkg/test /Data/GitHub/forked-minisketch/cmake-build-vcpkg/test/CMakeFiles/minisketch_test.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : test/CMakeFiles/minisketch_test.dir/depend

