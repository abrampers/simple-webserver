# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.12

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
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.12.2/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.12.2/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/Users/abrampers/Documents/Academics/7th Semester/PAT/Tugas1/c++"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/Users/abrampers/Documents/Academics/7th Semester/PAT/Tugas1/c++/build"

# Utility rule file for NightlyTest.

# Include the progress variables for this target.
include lib/libuv/CMakeFiles/NightlyTest.dir/progress.make

lib/libuv/CMakeFiles/NightlyTest:
	cd "/Users/abrampers/Documents/Academics/7th Semester/PAT/Tugas1/c++/build/lib/libuv" && /usr/local/Cellar/cmake/3.12.2/bin/ctest -D NightlyTest

NightlyTest: lib/libuv/CMakeFiles/NightlyTest
NightlyTest: lib/libuv/CMakeFiles/NightlyTest.dir/build.make

.PHONY : NightlyTest

# Rule to build all files generated by this target.
lib/libuv/CMakeFiles/NightlyTest.dir/build: NightlyTest

.PHONY : lib/libuv/CMakeFiles/NightlyTest.dir/build

lib/libuv/CMakeFiles/NightlyTest.dir/clean:
	cd "/Users/abrampers/Documents/Academics/7th Semester/PAT/Tugas1/c++/build/lib/libuv" && $(CMAKE_COMMAND) -P CMakeFiles/NightlyTest.dir/cmake_clean.cmake
.PHONY : lib/libuv/CMakeFiles/NightlyTest.dir/clean

lib/libuv/CMakeFiles/NightlyTest.dir/depend:
	cd "/Users/abrampers/Documents/Academics/7th Semester/PAT/Tugas1/c++/build" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/Users/abrampers/Documents/Academics/7th Semester/PAT/Tugas1/c++" "/Users/abrampers/Documents/Academics/7th Semester/PAT/Tugas1/c++/lib/libuv" "/Users/abrampers/Documents/Academics/7th Semester/PAT/Tugas1/c++/build" "/Users/abrampers/Documents/Academics/7th Semester/PAT/Tugas1/c++/build/lib/libuv" "/Users/abrampers/Documents/Academics/7th Semester/PAT/Tugas1/c++/build/lib/libuv/CMakeFiles/NightlyTest.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : lib/libuv/CMakeFiles/NightlyTest.dir/depend

