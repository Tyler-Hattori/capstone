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
CMAKE_SOURCE_DIR = /home/ubuntu/f1tenth/src

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ubuntu/f1tenth/build

# Utility rule file for velma_genlisp.

# Include the progress variables for this target.
include velma/CMakeFiles/velma_genlisp.dir/progress.make

velma_genlisp: velma/CMakeFiles/velma_genlisp.dir/build.make

.PHONY : velma_genlisp

# Rule to build all files generated by this target.
velma/CMakeFiles/velma_genlisp.dir/build: velma_genlisp

.PHONY : velma/CMakeFiles/velma_genlisp.dir/build

velma/CMakeFiles/velma_genlisp.dir/clean:
	cd /home/ubuntu/f1tenth/build/velma && $(CMAKE_COMMAND) -P CMakeFiles/velma_genlisp.dir/cmake_clean.cmake
.PHONY : velma/CMakeFiles/velma_genlisp.dir/clean

velma/CMakeFiles/velma_genlisp.dir/depend:
	cd /home/ubuntu/f1tenth/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ubuntu/f1tenth/src /home/ubuntu/f1tenth/src/velma /home/ubuntu/f1tenth/build /home/ubuntu/f1tenth/build/velma /home/ubuntu/f1tenth/build/velma/CMakeFiles/velma_genlisp.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : velma/CMakeFiles/velma_genlisp.dir/depend

