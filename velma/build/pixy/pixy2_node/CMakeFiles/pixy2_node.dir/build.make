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

# Include any dependencies generated for this target.
include pixy/pixy2_node/CMakeFiles/pixy2_node.dir/depend.make

# Include the progress variables for this target.
include pixy/pixy2_node/CMakeFiles/pixy2_node.dir/progress.make

# Include the compile flags for this target's objects.
include pixy/pixy2_node/CMakeFiles/pixy2_node.dir/flags.make

pixy/pixy2_node/CMakeFiles/pixy2_node.dir/src/pixy2_node.cpp.o: pixy/pixy2_node/CMakeFiles/pixy2_node.dir/flags.make
pixy/pixy2_node/CMakeFiles/pixy2_node.dir/src/pixy2_node.cpp.o: /home/ubuntu/capstone/velma/src/pixy/pixy2_node/src/pixy2_node.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ubuntu/capstone/velma/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object pixy/pixy2_node/CMakeFiles/pixy2_node.dir/src/pixy2_node.cpp.o"
	cd /home/ubuntu/capstone/velma/build/pixy/pixy2_node && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/pixy2_node.dir/src/pixy2_node.cpp.o -c /home/ubuntu/capstone/velma/src/pixy/pixy2_node/src/pixy2_node.cpp

pixy/pixy2_node/CMakeFiles/pixy2_node.dir/src/pixy2_node.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/pixy2_node.dir/src/pixy2_node.cpp.i"
	cd /home/ubuntu/capstone/velma/build/pixy/pixy2_node && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ubuntu/capstone/velma/src/pixy/pixy2_node/src/pixy2_node.cpp > CMakeFiles/pixy2_node.dir/src/pixy2_node.cpp.i

pixy/pixy2_node/CMakeFiles/pixy2_node.dir/src/pixy2_node.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/pixy2_node.dir/src/pixy2_node.cpp.s"
	cd /home/ubuntu/capstone/velma/build/pixy/pixy2_node && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ubuntu/capstone/velma/src/pixy/pixy2_node/src/pixy2_node.cpp -o CMakeFiles/pixy2_node.dir/src/pixy2_node.cpp.s

# Object files for target pixy2_node
pixy2_node_OBJECTS = \
"CMakeFiles/pixy2_node.dir/src/pixy2_node.cpp.o"

# External object files for target pixy2_node
pixy2_node_EXTERNAL_OBJECTS =

/home/ubuntu/capstone/velma/devel/lib/pixy2_node/pixy2_node: pixy/pixy2_node/CMakeFiles/pixy2_node.dir/src/pixy2_node.cpp.o
/home/ubuntu/capstone/velma/devel/lib/pixy2_node/pixy2_node: pixy/pixy2_node/CMakeFiles/pixy2_node.dir/build.make
/home/ubuntu/capstone/velma/devel/lib/pixy2_node/pixy2_node: /opt/ros/noetic/lib/libroscpp.so
/home/ubuntu/capstone/velma/devel/lib/pixy2_node/pixy2_node: /usr/lib/aarch64-linux-gnu/libpthread.so
/home/ubuntu/capstone/velma/devel/lib/pixy2_node/pixy2_node: /usr/lib/aarch64-linux-gnu/libboost_chrono.so.1.71.0
/home/ubuntu/capstone/velma/devel/lib/pixy2_node/pixy2_node: /usr/lib/aarch64-linux-gnu/libboost_filesystem.so.1.71.0
/home/ubuntu/capstone/velma/devel/lib/pixy2_node/pixy2_node: /opt/ros/noetic/lib/librosconsole.so
/home/ubuntu/capstone/velma/devel/lib/pixy2_node/pixy2_node: /opt/ros/noetic/lib/librosconsole_log4cxx.so
/home/ubuntu/capstone/velma/devel/lib/pixy2_node/pixy2_node: /opt/ros/noetic/lib/librosconsole_backend_interface.so
/home/ubuntu/capstone/velma/devel/lib/pixy2_node/pixy2_node: /usr/lib/aarch64-linux-gnu/liblog4cxx.so
/home/ubuntu/capstone/velma/devel/lib/pixy2_node/pixy2_node: /usr/lib/aarch64-linux-gnu/libboost_regex.so.1.71.0
/home/ubuntu/capstone/velma/devel/lib/pixy2_node/pixy2_node: /opt/ros/noetic/lib/libroscpp_serialization.so
/home/ubuntu/capstone/velma/devel/lib/pixy2_node/pixy2_node: /opt/ros/noetic/lib/libxmlrpcpp.so
/home/ubuntu/capstone/velma/devel/lib/pixy2_node/pixy2_node: /opt/ros/noetic/lib/librostime.so
/home/ubuntu/capstone/velma/devel/lib/pixy2_node/pixy2_node: /usr/lib/aarch64-linux-gnu/libboost_date_time.so.1.71.0
/home/ubuntu/capstone/velma/devel/lib/pixy2_node/pixy2_node: /opt/ros/noetic/lib/libcpp_common.so
/home/ubuntu/capstone/velma/devel/lib/pixy2_node/pixy2_node: /usr/lib/aarch64-linux-gnu/libboost_system.so.1.71.0
/home/ubuntu/capstone/velma/devel/lib/pixy2_node/pixy2_node: /usr/lib/aarch64-linux-gnu/libboost_thread.so.1.71.0
/home/ubuntu/capstone/velma/devel/lib/pixy2_node/pixy2_node: /usr/lib/aarch64-linux-gnu/libconsole_bridge.so.0.4
/home/ubuntu/capstone/velma/devel/lib/pixy2_node/pixy2_node: /home/ubuntu/capstone/velma/src/pixy/pixy2_node/pixy2/build/libpixyusb2/libpixy2.a
/home/ubuntu/capstone/velma/devel/lib/pixy2_node/pixy2_node: /usr/lib/aarch64-linux-gnu/libusb-1.0.so
/home/ubuntu/capstone/velma/devel/lib/pixy2_node/pixy2_node: pixy/pixy2_node/CMakeFiles/pixy2_node.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/ubuntu/capstone/velma/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable /home/ubuntu/capstone/velma/devel/lib/pixy2_node/pixy2_node"
	cd /home/ubuntu/capstone/velma/build/pixy/pixy2_node && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/pixy2_node.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
pixy/pixy2_node/CMakeFiles/pixy2_node.dir/build: /home/ubuntu/capstone/velma/devel/lib/pixy2_node/pixy2_node

.PHONY : pixy/pixy2_node/CMakeFiles/pixy2_node.dir/build

pixy/pixy2_node/CMakeFiles/pixy2_node.dir/clean:
	cd /home/ubuntu/capstone/velma/build/pixy/pixy2_node && $(CMAKE_COMMAND) -P CMakeFiles/pixy2_node.dir/cmake_clean.cmake
.PHONY : pixy/pixy2_node/CMakeFiles/pixy2_node.dir/clean

pixy/pixy2_node/CMakeFiles/pixy2_node.dir/depend:
	cd /home/ubuntu/capstone/velma/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ubuntu/capstone/velma/src /home/ubuntu/capstone/velma/src/pixy/pixy2_node /home/ubuntu/capstone/velma/build /home/ubuntu/capstone/velma/build/pixy/pixy2_node /home/ubuntu/capstone/velma/build/pixy/pixy2_node/CMakeFiles/pixy2_node.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : pixy/pixy2_node/CMakeFiles/pixy2_node.dir/depend

