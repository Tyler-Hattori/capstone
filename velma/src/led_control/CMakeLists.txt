cmake_minimum_required(VERSION 3.0.2)
project(led_control)

find_package(catkin REQUIRED COMPONENTS
  ackermann_msgs
  geometry_msgs
  message_generation
  nav_msgs
  roscpp
  rospy
  std_msgs
)

catkin_package(
 # INCLUDE_DIRS include
  #LIBRARIES indicators
  CATKIN_DEPENDS ackermann_msgs geometry_msgs nav_msgs roscpp rospy std_msgs
#  DEPENDS system_lib
)

include_directories(
  ${catkin_INCLUDE_DIRS}
)

 # Add the nodes
  file(GLOB NODE_SRC_FILES node/*.cpp)
  foreach(_node_file ${NODE_SRC_FILES})
      get_filename_component(_node_name ${_node_file} NAME_WE)
      add_executable(${_node_name} ${_node_file})
      #target_link_libraries(${_node_name} ${LIBS})
      #add_dependencies(${_node_name} led_control_generate_messages_cpp)
  endforeach()
