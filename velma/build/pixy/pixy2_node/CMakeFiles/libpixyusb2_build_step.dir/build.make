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
CMAKE_SOURCE_DIR = /home/thattori/capstone/F1Tenth/velma/src

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/thattori/capstone/F1Tenth/velma/build

# Utility rule file for libpixyusb2_build_step.

# Include the progress variables for this target.
include pixy/pixy2_node/CMakeFiles/libpixyusb2_build_step.dir/progress.make

pixy/pixy2_node/CMakeFiles/libpixyusb2_build_step:
	cd /home/thattori/capstone/F1Tenth/velma/src/pixy/pixy2_node/pixy2/scripts && /home/thattori/capstone/F1Tenth/velma/src/pixy/pixy2_node/pixy2/scripts/build_libpixyusb2.sh

libpixyusb2_build_step: pixy/pixy2_node/CMakeFiles/libpixyusb2_build_step
libpixyusb2_build_step: pixy/pixy2_node/CMakeFiles/libpixyusb2_build_step.dir/build.make

.PHONY : libpixyusb2_build_step

# Rule to build all files generated by this target.
pixy/pixy2_node/CMakeFiles/libpixyusb2_build_step.dir/build: libpixyusb2_build_step

.PHONY : pixy/pixy2_node/CMakeFiles/libpixyusb2_build_step.dir/build

pixy/pixy2_node/CMakeFiles/libpixyusb2_build_step.dir/clean:
	cd /home/thattori/capstone/F1Tenth/velma/build/pixy/pixy2_node && $(CMAKE_COMMAND) -P CMakeFiles/libpixyusb2_build_step.dir/cmake_clean.cmake
.PHONY : pixy/pixy2_node/CMakeFiles/libpixyusb2_build_step.dir/clean

pixy/pixy2_node/CMakeFiles/libpixyusb2_build_step.dir/depend:
	cd /home/thattori/capstone/F1Tenth/velma/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/thattori/capstone/F1Tenth/velma/src /home/thattori/capstone/F1Tenth/velma/src/pixy/pixy2_node /home/thattori/capstone/F1Tenth/velma/build /home/thattori/capstone/F1Tenth/velma/build/pixy/pixy2_node /home/thattori/capstone/F1Tenth/velma/build/pixy/pixy2_node/CMakeFiles/libpixyusb2_build_step.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : pixy/pixy2_node/CMakeFiles/libpixyusb2_build_step.dir/depend

