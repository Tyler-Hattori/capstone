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
CMAKE_SOURCE_DIR = /home/ubuntu/capstone/velma/src

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ubuntu/capstone/velma/build

# Utility rule file for pixy2_msgs_gencpp.

# Include the progress variables for this target.
include pixy/pixy2_msgs/CMakeFiles/pixy2_msgs_gencpp.dir/progress.make

pixy2_msgs_gencpp: pixy/pixy2_msgs/CMakeFiles/pixy2_msgs_gencpp.dir/build.make

.PHONY : pixy2_msgs_gencpp

# Rule to build all files generated by this target.
pixy/pixy2_msgs/CMakeFiles/pixy2_msgs_gencpp.dir/build: pixy2_msgs_gencpp

.PHONY : pixy/pixy2_msgs/CMakeFiles/pixy2_msgs_gencpp.dir/build

pixy/pixy2_msgs/CMakeFiles/pixy2_msgs_gencpp.dir/clean:
	cd /home/ubuntu/capstone/velma/build/pixy/pixy2_msgs && $(CMAKE_COMMAND) -P CMakeFiles/pixy2_msgs_gencpp.dir/cmake_clean.cmake
.PHONY : pixy/pixy2_msgs/CMakeFiles/pixy2_msgs_gencpp.dir/clean

pixy/pixy2_msgs/CMakeFiles/pixy2_msgs_gencpp.dir/depend:
	cd /home/ubuntu/capstone/velma/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ubuntu/capstone/velma/src /home/ubuntu/capstone/velma/src/pixy/pixy2_msgs /home/ubuntu/capstone/velma/build /home/ubuntu/capstone/velma/build/pixy/pixy2_msgs /home/ubuntu/capstone/velma/build/pixy/pixy2_msgs/CMakeFiles/pixy2_msgs_gencpp.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : pixy/pixy2_msgs/CMakeFiles/pixy2_msgs_gencpp.dir/depend

