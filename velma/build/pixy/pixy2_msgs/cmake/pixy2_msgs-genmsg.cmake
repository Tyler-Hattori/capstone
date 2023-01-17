# generated from genmsg/cmake/pkg-genmsg.cmake.em

message(STATUS "pixy2_msgs: 4 messages, 0 services")

set(MSG_I_FLAGS "-Ipixy2_msgs:/home/ubuntu/F1Tenth/velma/src/pixy/pixy2_msgs/msg;-Isensor_msgs:/opt/ros/noetic/share/sensor_msgs/cmake/../msg;-Igeometry_msgs:/opt/ros/noetic/share/geometry_msgs/cmake/../msg;-Istd_msgs:/opt/ros/noetic/share/std_msgs/cmake/../msg")

# Find all generators
find_package(gencpp REQUIRED)
find_package(geneus REQUIRED)
find_package(genlisp REQUIRED)
find_package(gennodejs REQUIRED)
find_package(genpy REQUIRED)

add_custom_target(pixy2_msgs_generate_messages ALL)

# verify that message/service dependencies have not changed since configure



get_filename_component(_filename "/home/ubuntu/F1Tenth/velma/src/pixy/pixy2_msgs/msg/PixyBlock.msg" NAME_WE)
add_custom_target(_pixy2_msgs_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "pixy2_msgs" "/home/ubuntu/F1Tenth/velma/src/pixy/pixy2_msgs/msg/PixyBlock.msg" "sensor_msgs/RegionOfInterest"
)

get_filename_component(_filename "/home/ubuntu/F1Tenth/velma/src/pixy/pixy2_msgs/msg/PixyData.msg" NAME_WE)
add_custom_target(_pixy2_msgs_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "pixy2_msgs" "/home/ubuntu/F1Tenth/velma/src/pixy/pixy2_msgs/msg/PixyData.msg" "sensor_msgs/RegionOfInterest:std_msgs/Header:pixy2_msgs/PixyBlock"
)

get_filename_component(_filename "/home/ubuntu/F1Tenth/velma/src/pixy/pixy2_msgs/msg/Servo.msg" NAME_WE)
add_custom_target(_pixy2_msgs_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "pixy2_msgs" "/home/ubuntu/F1Tenth/velma/src/pixy/pixy2_msgs/msg/Servo.msg" ""
)

get_filename_component(_filename "/home/ubuntu/F1Tenth/velma/src/pixy/pixy2_msgs/msg/PixyResolution.msg" NAME_WE)
add_custom_target(_pixy2_msgs_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "pixy2_msgs" "/home/ubuntu/F1Tenth/velma/src/pixy/pixy2_msgs/msg/PixyResolution.msg" ""
)

#
#  langs = gencpp;geneus;genlisp;gennodejs;genpy
#

### Section generating for lang: gencpp
### Generating Messages
_generate_msg_cpp(pixy2_msgs
  "/home/ubuntu/F1Tenth/velma/src/pixy/pixy2_msgs/msg/PixyBlock.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/sensor_msgs/cmake/../msg/RegionOfInterest.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/pixy2_msgs
)
_generate_msg_cpp(pixy2_msgs
  "/home/ubuntu/F1Tenth/velma/src/pixy/pixy2_msgs/msg/PixyData.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/sensor_msgs/cmake/../msg/RegionOfInterest.msg;/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg;/home/ubuntu/F1Tenth/velma/src/pixy/pixy2_msgs/msg/PixyBlock.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/pixy2_msgs
)
_generate_msg_cpp(pixy2_msgs
  "/home/ubuntu/F1Tenth/velma/src/pixy/pixy2_msgs/msg/Servo.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/pixy2_msgs
)
_generate_msg_cpp(pixy2_msgs
  "/home/ubuntu/F1Tenth/velma/src/pixy/pixy2_msgs/msg/PixyResolution.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/pixy2_msgs
)

### Generating Services

### Generating Module File
_generate_module_cpp(pixy2_msgs
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/pixy2_msgs
  "${ALL_GEN_OUTPUT_FILES_cpp}"
)

add_custom_target(pixy2_msgs_generate_messages_cpp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_cpp}
)
add_dependencies(pixy2_msgs_generate_messages pixy2_msgs_generate_messages_cpp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/ubuntu/F1Tenth/velma/src/pixy/pixy2_msgs/msg/PixyBlock.msg" NAME_WE)
add_dependencies(pixy2_msgs_generate_messages_cpp _pixy2_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/ubuntu/F1Tenth/velma/src/pixy/pixy2_msgs/msg/PixyData.msg" NAME_WE)
add_dependencies(pixy2_msgs_generate_messages_cpp _pixy2_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/ubuntu/F1Tenth/velma/src/pixy/pixy2_msgs/msg/Servo.msg" NAME_WE)
add_dependencies(pixy2_msgs_generate_messages_cpp _pixy2_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/ubuntu/F1Tenth/velma/src/pixy/pixy2_msgs/msg/PixyResolution.msg" NAME_WE)
add_dependencies(pixy2_msgs_generate_messages_cpp _pixy2_msgs_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(pixy2_msgs_gencpp)
add_dependencies(pixy2_msgs_gencpp pixy2_msgs_generate_messages_cpp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS pixy2_msgs_generate_messages_cpp)

### Section generating for lang: geneus
### Generating Messages
_generate_msg_eus(pixy2_msgs
  "/home/ubuntu/F1Tenth/velma/src/pixy/pixy2_msgs/msg/PixyBlock.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/sensor_msgs/cmake/../msg/RegionOfInterest.msg"
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/pixy2_msgs
)
_generate_msg_eus(pixy2_msgs
  "/home/ubuntu/F1Tenth/velma/src/pixy/pixy2_msgs/msg/PixyData.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/sensor_msgs/cmake/../msg/RegionOfInterest.msg;/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg;/home/ubuntu/F1Tenth/velma/src/pixy/pixy2_msgs/msg/PixyBlock.msg"
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/pixy2_msgs
)
_generate_msg_eus(pixy2_msgs
  "/home/ubuntu/F1Tenth/velma/src/pixy/pixy2_msgs/msg/Servo.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/pixy2_msgs
)
_generate_msg_eus(pixy2_msgs
  "/home/ubuntu/F1Tenth/velma/src/pixy/pixy2_msgs/msg/PixyResolution.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/pixy2_msgs
)

### Generating Services

### Generating Module File
_generate_module_eus(pixy2_msgs
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/pixy2_msgs
  "${ALL_GEN_OUTPUT_FILES_eus}"
)

add_custom_target(pixy2_msgs_generate_messages_eus
  DEPENDS ${ALL_GEN_OUTPUT_FILES_eus}
)
add_dependencies(pixy2_msgs_generate_messages pixy2_msgs_generate_messages_eus)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/ubuntu/F1Tenth/velma/src/pixy/pixy2_msgs/msg/PixyBlock.msg" NAME_WE)
add_dependencies(pixy2_msgs_generate_messages_eus _pixy2_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/ubuntu/F1Tenth/velma/src/pixy/pixy2_msgs/msg/PixyData.msg" NAME_WE)
add_dependencies(pixy2_msgs_generate_messages_eus _pixy2_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/ubuntu/F1Tenth/velma/src/pixy/pixy2_msgs/msg/Servo.msg" NAME_WE)
add_dependencies(pixy2_msgs_generate_messages_eus _pixy2_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/ubuntu/F1Tenth/velma/src/pixy/pixy2_msgs/msg/PixyResolution.msg" NAME_WE)
add_dependencies(pixy2_msgs_generate_messages_eus _pixy2_msgs_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(pixy2_msgs_geneus)
add_dependencies(pixy2_msgs_geneus pixy2_msgs_generate_messages_eus)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS pixy2_msgs_generate_messages_eus)

### Section generating for lang: genlisp
### Generating Messages
_generate_msg_lisp(pixy2_msgs
  "/home/ubuntu/F1Tenth/velma/src/pixy/pixy2_msgs/msg/PixyBlock.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/sensor_msgs/cmake/../msg/RegionOfInterest.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/pixy2_msgs
)
_generate_msg_lisp(pixy2_msgs
  "/home/ubuntu/F1Tenth/velma/src/pixy/pixy2_msgs/msg/PixyData.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/sensor_msgs/cmake/../msg/RegionOfInterest.msg;/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg;/home/ubuntu/F1Tenth/velma/src/pixy/pixy2_msgs/msg/PixyBlock.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/pixy2_msgs
)
_generate_msg_lisp(pixy2_msgs
  "/home/ubuntu/F1Tenth/velma/src/pixy/pixy2_msgs/msg/Servo.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/pixy2_msgs
)
_generate_msg_lisp(pixy2_msgs
  "/home/ubuntu/F1Tenth/velma/src/pixy/pixy2_msgs/msg/PixyResolution.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/pixy2_msgs
)

### Generating Services

### Generating Module File
_generate_module_lisp(pixy2_msgs
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/pixy2_msgs
  "${ALL_GEN_OUTPUT_FILES_lisp}"
)

add_custom_target(pixy2_msgs_generate_messages_lisp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_lisp}
)
add_dependencies(pixy2_msgs_generate_messages pixy2_msgs_generate_messages_lisp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/ubuntu/F1Tenth/velma/src/pixy/pixy2_msgs/msg/PixyBlock.msg" NAME_WE)
add_dependencies(pixy2_msgs_generate_messages_lisp _pixy2_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/ubuntu/F1Tenth/velma/src/pixy/pixy2_msgs/msg/PixyData.msg" NAME_WE)
add_dependencies(pixy2_msgs_generate_messages_lisp _pixy2_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/ubuntu/F1Tenth/velma/src/pixy/pixy2_msgs/msg/Servo.msg" NAME_WE)
add_dependencies(pixy2_msgs_generate_messages_lisp _pixy2_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/ubuntu/F1Tenth/velma/src/pixy/pixy2_msgs/msg/PixyResolution.msg" NAME_WE)
add_dependencies(pixy2_msgs_generate_messages_lisp _pixy2_msgs_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(pixy2_msgs_genlisp)
add_dependencies(pixy2_msgs_genlisp pixy2_msgs_generate_messages_lisp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS pixy2_msgs_generate_messages_lisp)

### Section generating for lang: gennodejs
### Generating Messages
_generate_msg_nodejs(pixy2_msgs
  "/home/ubuntu/F1Tenth/velma/src/pixy/pixy2_msgs/msg/PixyBlock.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/sensor_msgs/cmake/../msg/RegionOfInterest.msg"
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/pixy2_msgs
)
_generate_msg_nodejs(pixy2_msgs
  "/home/ubuntu/F1Tenth/velma/src/pixy/pixy2_msgs/msg/PixyData.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/sensor_msgs/cmake/../msg/RegionOfInterest.msg;/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg;/home/ubuntu/F1Tenth/velma/src/pixy/pixy2_msgs/msg/PixyBlock.msg"
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/pixy2_msgs
)
_generate_msg_nodejs(pixy2_msgs
  "/home/ubuntu/F1Tenth/velma/src/pixy/pixy2_msgs/msg/Servo.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/pixy2_msgs
)
_generate_msg_nodejs(pixy2_msgs
  "/home/ubuntu/F1Tenth/velma/src/pixy/pixy2_msgs/msg/PixyResolution.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/pixy2_msgs
)

### Generating Services

### Generating Module File
_generate_module_nodejs(pixy2_msgs
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/pixy2_msgs
  "${ALL_GEN_OUTPUT_FILES_nodejs}"
)

add_custom_target(pixy2_msgs_generate_messages_nodejs
  DEPENDS ${ALL_GEN_OUTPUT_FILES_nodejs}
)
add_dependencies(pixy2_msgs_generate_messages pixy2_msgs_generate_messages_nodejs)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/ubuntu/F1Tenth/velma/src/pixy/pixy2_msgs/msg/PixyBlock.msg" NAME_WE)
add_dependencies(pixy2_msgs_generate_messages_nodejs _pixy2_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/ubuntu/F1Tenth/velma/src/pixy/pixy2_msgs/msg/PixyData.msg" NAME_WE)
add_dependencies(pixy2_msgs_generate_messages_nodejs _pixy2_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/ubuntu/F1Tenth/velma/src/pixy/pixy2_msgs/msg/Servo.msg" NAME_WE)
add_dependencies(pixy2_msgs_generate_messages_nodejs _pixy2_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/ubuntu/F1Tenth/velma/src/pixy/pixy2_msgs/msg/PixyResolution.msg" NAME_WE)
add_dependencies(pixy2_msgs_generate_messages_nodejs _pixy2_msgs_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(pixy2_msgs_gennodejs)
add_dependencies(pixy2_msgs_gennodejs pixy2_msgs_generate_messages_nodejs)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS pixy2_msgs_generate_messages_nodejs)

### Section generating for lang: genpy
### Generating Messages
_generate_msg_py(pixy2_msgs
  "/home/ubuntu/F1Tenth/velma/src/pixy/pixy2_msgs/msg/PixyBlock.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/sensor_msgs/cmake/../msg/RegionOfInterest.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/pixy2_msgs
)
_generate_msg_py(pixy2_msgs
  "/home/ubuntu/F1Tenth/velma/src/pixy/pixy2_msgs/msg/PixyData.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/sensor_msgs/cmake/../msg/RegionOfInterest.msg;/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg;/home/ubuntu/F1Tenth/velma/src/pixy/pixy2_msgs/msg/PixyBlock.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/pixy2_msgs
)
_generate_msg_py(pixy2_msgs
  "/home/ubuntu/F1Tenth/velma/src/pixy/pixy2_msgs/msg/Servo.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/pixy2_msgs
)
_generate_msg_py(pixy2_msgs
  "/home/ubuntu/F1Tenth/velma/src/pixy/pixy2_msgs/msg/PixyResolution.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/pixy2_msgs
)

### Generating Services

### Generating Module File
_generate_module_py(pixy2_msgs
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/pixy2_msgs
  "${ALL_GEN_OUTPUT_FILES_py}"
)

add_custom_target(pixy2_msgs_generate_messages_py
  DEPENDS ${ALL_GEN_OUTPUT_FILES_py}
)
add_dependencies(pixy2_msgs_generate_messages pixy2_msgs_generate_messages_py)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/ubuntu/F1Tenth/velma/src/pixy/pixy2_msgs/msg/PixyBlock.msg" NAME_WE)
add_dependencies(pixy2_msgs_generate_messages_py _pixy2_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/ubuntu/F1Tenth/velma/src/pixy/pixy2_msgs/msg/PixyData.msg" NAME_WE)
add_dependencies(pixy2_msgs_generate_messages_py _pixy2_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/ubuntu/F1Tenth/velma/src/pixy/pixy2_msgs/msg/Servo.msg" NAME_WE)
add_dependencies(pixy2_msgs_generate_messages_py _pixy2_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/ubuntu/F1Tenth/velma/src/pixy/pixy2_msgs/msg/PixyResolution.msg" NAME_WE)
add_dependencies(pixy2_msgs_generate_messages_py _pixy2_msgs_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(pixy2_msgs_genpy)
add_dependencies(pixy2_msgs_genpy pixy2_msgs_generate_messages_py)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS pixy2_msgs_generate_messages_py)



if(gencpp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/pixy2_msgs)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/pixy2_msgs
    DESTINATION ${gencpp_INSTALL_DIR}
  )
endif()
if(TARGET sensor_msgs_generate_messages_cpp)
  add_dependencies(pixy2_msgs_generate_messages_cpp sensor_msgs_generate_messages_cpp)
endif()

if(geneus_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/pixy2_msgs)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/pixy2_msgs
    DESTINATION ${geneus_INSTALL_DIR}
  )
endif()
if(TARGET sensor_msgs_generate_messages_eus)
  add_dependencies(pixy2_msgs_generate_messages_eus sensor_msgs_generate_messages_eus)
endif()

if(genlisp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/pixy2_msgs)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/pixy2_msgs
    DESTINATION ${genlisp_INSTALL_DIR}
  )
endif()
if(TARGET sensor_msgs_generate_messages_lisp)
  add_dependencies(pixy2_msgs_generate_messages_lisp sensor_msgs_generate_messages_lisp)
endif()

if(gennodejs_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/pixy2_msgs)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/pixy2_msgs
    DESTINATION ${gennodejs_INSTALL_DIR}
  )
endif()
if(TARGET sensor_msgs_generate_messages_nodejs)
  add_dependencies(pixy2_msgs_generate_messages_nodejs sensor_msgs_generate_messages_nodejs)
endif()

if(genpy_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/pixy2_msgs)
  install(CODE "execute_process(COMMAND \"/usr/bin/python3\" -m compileall \"${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/pixy2_msgs\")")
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/pixy2_msgs
    DESTINATION ${genpy_INSTALL_DIR}
  )
endif()
if(TARGET sensor_msgs_generate_messages_py)
  add_dependencies(pixy2_msgs_generate_messages_py sensor_msgs_generate_messages_py)
endif()
