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

add_message_files(
    FILES
    gpiowrite.msg
  )

generate_messages(
  DEPENDENCIES
  std_msgs
  nav_msgs
  ackermann_msgs
  geometry_msgs
  
  )

catkin_package(
  INCLUDE_DIRS include
  #LIBRARIES led_control
  CATKIN_DEPENDS roscpp message_runtime ackermann_msgs geometry_msgs nav_msgs rospy std_msgs
#  DEPENDS system_lib
)

include_directories(include ${catkin_INCLUDE_DIRS})

add_executable(indicator node/indicator.cpp)
target_link_libraries(indicator ${catkin_LIBRARIES})
add_dependencies(indicator led_control_generate_messages_cpp)

add_executable(blind_spot node/blind_spot.cpp)
target_link_libraries(blind_spot ${catkin_LIBRARIES})
add_dependencies(blind_spot led_control_generate_messages_cpp)

add_executable(manual node/manual.cpp)
target_link_libraries(manual ${catkin_LIBRARIES})
add_dependencies(manual led_control_generate_messages_cpp)
