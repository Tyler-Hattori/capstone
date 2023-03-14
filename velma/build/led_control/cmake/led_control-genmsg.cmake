# generated from genmsg/cmake/pkg-genmsg.cmake.em

message(STATUS "led_control: 1 messages, 0 services")

set(MSG_I_FLAGS "-Iled_control:/home/thattori/capstone/velma/src/led_control/msg;-Istd_msgs:/opt/ros/noetic/share/std_msgs/cmake/../msg;-Inav_msgs:/opt/ros/noetic/share/nav_msgs/cmake/../msg;-Iackermann_msgs:/opt/ros/noetic/share/ackermann_msgs/cmake/../msg;-Igeometry_msgs:/opt/ros/noetic/share/geometry_msgs/cmake/../msg;-Iactionlib_msgs:/opt/ros/noetic/share/actionlib_msgs/cmake/../msg")

# Find all generators
find_package(gencpp REQUIRED)
find_package(geneus REQUIRED)
find_package(genlisp REQUIRED)
find_package(gennodejs REQUIRED)
find_package(genpy REQUIRED)

add_custom_target(led_control_generate_messages ALL)

# verify that message/service dependencies have not changed since configure



get_filename_component(_filename "/home/thattori/capstone/velma/src/led_control/msg/gpiowrite.msg" NAME_WE)
add_custom_target(_led_control_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "led_control" "/home/thattori/capstone/velma/src/led_control/msg/gpiowrite.msg" ""
)

#
#  langs = gencpp;geneus;genlisp;gennodejs;genpy
#

### Section generating for lang: gencpp
### Generating Messages
_generate_msg_cpp(led_control
  "/home/thattori/capstone/velma/src/led_control/msg/gpiowrite.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/led_control
)

### Generating Services

### Generating Module File
_generate_module_cpp(led_control
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/led_control
  "${ALL_GEN_OUTPUT_FILES_cpp}"
)

add_custom_target(led_control_generate_messages_cpp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_cpp}
)
add_dependencies(led_control_generate_messages led_control_generate_messages_cpp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/thattori/capstone/velma/src/led_control/msg/gpiowrite.msg" NAME_WE)
add_dependencies(led_control_generate_messages_cpp _led_control_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(led_control_gencpp)
add_dependencies(led_control_gencpp led_control_generate_messages_cpp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS led_control_generate_messages_cpp)

### Section generating for lang: geneus
### Generating Messages
_generate_msg_eus(led_control
  "/home/thattori/capstone/velma/src/led_control/msg/gpiowrite.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/led_control
)

### Generating Services

### Generating Module File
_generate_module_eus(led_control
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/led_control
  "${ALL_GEN_OUTPUT_FILES_eus}"
)

add_custom_target(led_control_generate_messages_eus
  DEPENDS ${ALL_GEN_OUTPUT_FILES_eus}
)
add_dependencies(led_control_generate_messages led_control_generate_messages_eus)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/thattori/capstone/velma/src/led_control/msg/gpiowrite.msg" NAME_WE)
add_dependencies(led_control_generate_messages_eus _led_control_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(led_control_geneus)
add_dependencies(led_control_geneus led_control_generate_messages_eus)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS led_control_generate_messages_eus)

### Section generating for lang: genlisp
### Generating Messages
_generate_msg_lisp(led_control
  "/home/thattori/capstone/velma/src/led_control/msg/gpiowrite.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/led_control
)

### Generating Services

### Generating Module File
_generate_module_lisp(led_control
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/led_control
  "${ALL_GEN_OUTPUT_FILES_lisp}"
)

add_custom_target(led_control_generate_messages_lisp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_lisp}
)
add_dependencies(led_control_generate_messages led_control_generate_messages_lisp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/thattori/capstone/velma/src/led_control/msg/gpiowrite.msg" NAME_WE)
add_dependencies(led_control_generate_messages_lisp _led_control_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(led_control_genlisp)
add_dependencies(led_control_genlisp led_control_generate_messages_lisp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS led_control_generate_messages_lisp)

### Section generating for lang: gennodejs
### Generating Messages
_generate_msg_nodejs(led_control
  "/home/thattori/capstone/velma/src/led_control/msg/gpiowrite.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/led_control
)

### Generating Services

### Generating Module File
_generate_module_nodejs(led_control
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/led_control
  "${ALL_GEN_OUTPUT_FILES_nodejs}"
)

add_custom_target(led_control_generate_messages_nodejs
  DEPENDS ${ALL_GEN_OUTPUT_FILES_nodejs}
)
add_dependencies(led_control_generate_messages led_control_generate_messages_nodejs)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/thattori/capstone/velma/src/led_control/msg/gpiowrite.msg" NAME_WE)
add_dependencies(led_control_generate_messages_nodejs _led_control_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(led_control_gennodejs)
add_dependencies(led_control_gennodejs led_control_generate_messages_nodejs)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS led_control_generate_messages_nodejs)

### Section generating for lang: genpy
### Generating Messages
_generate_msg_py(led_control
  "/home/thattori/capstone/velma/src/led_control/msg/gpiowrite.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/led_control
)

### Generating Services

### Generating Module File
_generate_module_py(led_control
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/led_control
  "${ALL_GEN_OUTPUT_FILES_py}"
)

add_custom_target(led_control_generate_messages_py
  DEPENDS ${ALL_GEN_OUTPUT_FILES_py}
)
add_dependencies(led_control_generate_messages led_control_generate_messages_py)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/thattori/capstone/velma/src/led_control/msg/gpiowrite.msg" NAME_WE)
add_dependencies(led_control_generate_messages_py _led_control_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(led_control_genpy)
add_dependencies(led_control_genpy led_control_generate_messages_py)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS led_control_generate_messages_py)



if(gencpp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/led_control)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/led_control
    DESTINATION ${gencpp_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_cpp)
  add_dependencies(led_control_generate_messages_cpp std_msgs_generate_messages_cpp)
endif()
if(TARGET nav_msgs_generate_messages_cpp)
  add_dependencies(led_control_generate_messages_cpp nav_msgs_generate_messages_cpp)
endif()
if(TARGET ackermann_msgs_generate_messages_cpp)
  add_dependencies(led_control_generate_messages_cpp ackermann_msgs_generate_messages_cpp)
endif()
if(TARGET geometry_msgs_generate_messages_cpp)
  add_dependencies(led_control_generate_messages_cpp geometry_msgs_generate_messages_cpp)
endif()

if(geneus_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/led_control)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/led_control
    DESTINATION ${geneus_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_eus)
  add_dependencies(led_control_generate_messages_eus std_msgs_generate_messages_eus)
endif()
if(TARGET nav_msgs_generate_messages_eus)
  add_dependencies(led_control_generate_messages_eus nav_msgs_generate_messages_eus)
endif()
if(TARGET ackermann_msgs_generate_messages_eus)
  add_dependencies(led_control_generate_messages_eus ackermann_msgs_generate_messages_eus)
endif()
if(TARGET geometry_msgs_generate_messages_eus)
  add_dependencies(led_control_generate_messages_eus geometry_msgs_generate_messages_eus)
endif()

if(genlisp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/led_control)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/led_control
    DESTINATION ${genlisp_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_lisp)
  add_dependencies(led_control_generate_messages_lisp std_msgs_generate_messages_lisp)
endif()
if(TARGET nav_msgs_generate_messages_lisp)
  add_dependencies(led_control_generate_messages_lisp nav_msgs_generate_messages_lisp)
endif()
if(TARGET ackermann_msgs_generate_messages_lisp)
  add_dependencies(led_control_generate_messages_lisp ackermann_msgs_generate_messages_lisp)
endif()
if(TARGET geometry_msgs_generate_messages_lisp)
  add_dependencies(led_control_generate_messages_lisp geometry_msgs_generate_messages_lisp)
endif()

if(gennodejs_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/led_control)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/led_control
    DESTINATION ${gennodejs_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_nodejs)
  add_dependencies(led_control_generate_messages_nodejs std_msgs_generate_messages_nodejs)
endif()
if(TARGET nav_msgs_generate_messages_nodejs)
  add_dependencies(led_control_generate_messages_nodejs nav_msgs_generate_messages_nodejs)
endif()
if(TARGET ackermann_msgs_generate_messages_nodejs)
  add_dependencies(led_control_generate_messages_nodejs ackermann_msgs_generate_messages_nodejs)
endif()
if(TARGET geometry_msgs_generate_messages_nodejs)
  add_dependencies(led_control_generate_messages_nodejs geometry_msgs_generate_messages_nodejs)
endif()

if(genpy_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/led_control)
  install(CODE "execute_process(COMMAND \"/usr/bin/python3\" -m compileall \"${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/led_control\")")
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/led_control
    DESTINATION ${genpy_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_py)
  add_dependencies(led_control_generate_messages_py std_msgs_generate_messages_py)
endif()
if(TARGET nav_msgs_generate_messages_py)
  add_dependencies(led_control_generate_messages_py nav_msgs_generate_messages_py)
endif()
if(TARGET ackermann_msgs_generate_messages_py)
  add_dependencies(led_control_generate_messages_py ackermann_msgs_generate_messages_py)
endif()
if(TARGET geometry_msgs_generate_messages_py)
  add_dependencies(led_control_generate_messages_py geometry_msgs_generate_messages_py)
endif()
