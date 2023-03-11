# generated from genmsg/cmake/pkg-genmsg.cmake.em

message(STATUS "gpio_control: 2 messages, 0 services")

set(MSG_I_FLAGS "-Igpio_control:/home/thattori/capstone/velma/src/gpio/msg;-Istd_msgs:/opt/ros/noetic/share/std_msgs/cmake/../msg")

# Find all generators
find_package(gencpp REQUIRED)
find_package(geneus REQUIRED)
find_package(genlisp REQUIRED)
find_package(gennodejs REQUIRED)
find_package(genpy REQUIRED)

add_custom_target(gpio_control_generate_messages ALL)

# verify that message/service dependencies have not changed since configure



get_filename_component(_filename "/home/thattori/capstone/velma/src/gpio/msg/InputState.msg" NAME_WE)
add_custom_target(_gpio_control_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "gpio_control" "/home/thattori/capstone/velma/src/gpio/msg/InputState.msg" "std_msgs/Header"
)

get_filename_component(_filename "/home/thattori/capstone/velma/src/gpio/msg/OutputState.msg" NAME_WE)
add_custom_target(_gpio_control_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "gpio_control" "/home/thattori/capstone/velma/src/gpio/msg/OutputState.msg" ""
)

#
#  langs = gencpp;geneus;genlisp;gennodejs;genpy
#

### Section generating for lang: gencpp
### Generating Messages
_generate_msg_cpp(gpio_control
  "/home/thattori/capstone/velma/src/gpio/msg/InputState.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/gpio_control
)
_generate_msg_cpp(gpio_control
  "/home/thattori/capstone/velma/src/gpio/msg/OutputState.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/gpio_control
)

### Generating Services

### Generating Module File
_generate_module_cpp(gpio_control
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/gpio_control
  "${ALL_GEN_OUTPUT_FILES_cpp}"
)

add_custom_target(gpio_control_generate_messages_cpp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_cpp}
)
add_dependencies(gpio_control_generate_messages gpio_control_generate_messages_cpp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/thattori/capstone/velma/src/gpio/msg/InputState.msg" NAME_WE)
add_dependencies(gpio_control_generate_messages_cpp _gpio_control_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/thattori/capstone/velma/src/gpio/msg/OutputState.msg" NAME_WE)
add_dependencies(gpio_control_generate_messages_cpp _gpio_control_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(gpio_control_gencpp)
add_dependencies(gpio_control_gencpp gpio_control_generate_messages_cpp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS gpio_control_generate_messages_cpp)

### Section generating for lang: geneus
### Generating Messages
_generate_msg_eus(gpio_control
  "/home/thattori/capstone/velma/src/gpio/msg/InputState.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/gpio_control
)
_generate_msg_eus(gpio_control
  "/home/thattori/capstone/velma/src/gpio/msg/OutputState.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/gpio_control
)

### Generating Services

### Generating Module File
_generate_module_eus(gpio_control
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/gpio_control
  "${ALL_GEN_OUTPUT_FILES_eus}"
)

add_custom_target(gpio_control_generate_messages_eus
  DEPENDS ${ALL_GEN_OUTPUT_FILES_eus}
)
add_dependencies(gpio_control_generate_messages gpio_control_generate_messages_eus)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/thattori/capstone/velma/src/gpio/msg/InputState.msg" NAME_WE)
add_dependencies(gpio_control_generate_messages_eus _gpio_control_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/thattori/capstone/velma/src/gpio/msg/OutputState.msg" NAME_WE)
add_dependencies(gpio_control_generate_messages_eus _gpio_control_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(gpio_control_geneus)
add_dependencies(gpio_control_geneus gpio_control_generate_messages_eus)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS gpio_control_generate_messages_eus)

### Section generating for lang: genlisp
### Generating Messages
_generate_msg_lisp(gpio_control
  "/home/thattori/capstone/velma/src/gpio/msg/InputState.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/gpio_control
)
_generate_msg_lisp(gpio_control
  "/home/thattori/capstone/velma/src/gpio/msg/OutputState.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/gpio_control
)

### Generating Services

### Generating Module File
_generate_module_lisp(gpio_control
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/gpio_control
  "${ALL_GEN_OUTPUT_FILES_lisp}"
)

add_custom_target(gpio_control_generate_messages_lisp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_lisp}
)
add_dependencies(gpio_control_generate_messages gpio_control_generate_messages_lisp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/thattori/capstone/velma/src/gpio/msg/InputState.msg" NAME_WE)
add_dependencies(gpio_control_generate_messages_lisp _gpio_control_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/thattori/capstone/velma/src/gpio/msg/OutputState.msg" NAME_WE)
add_dependencies(gpio_control_generate_messages_lisp _gpio_control_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(gpio_control_genlisp)
add_dependencies(gpio_control_genlisp gpio_control_generate_messages_lisp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS gpio_control_generate_messages_lisp)

### Section generating for lang: gennodejs
### Generating Messages
_generate_msg_nodejs(gpio_control
  "/home/thattori/capstone/velma/src/gpio/msg/InputState.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/gpio_control
)
_generate_msg_nodejs(gpio_control
  "/home/thattori/capstone/velma/src/gpio/msg/OutputState.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/gpio_control
)

### Generating Services

### Generating Module File
_generate_module_nodejs(gpio_control
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/gpio_control
  "${ALL_GEN_OUTPUT_FILES_nodejs}"
)

add_custom_target(gpio_control_generate_messages_nodejs
  DEPENDS ${ALL_GEN_OUTPUT_FILES_nodejs}
)
add_dependencies(gpio_control_generate_messages gpio_control_generate_messages_nodejs)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/thattori/capstone/velma/src/gpio/msg/InputState.msg" NAME_WE)
add_dependencies(gpio_control_generate_messages_nodejs _gpio_control_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/thattori/capstone/velma/src/gpio/msg/OutputState.msg" NAME_WE)
add_dependencies(gpio_control_generate_messages_nodejs _gpio_control_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(gpio_control_gennodejs)
add_dependencies(gpio_control_gennodejs gpio_control_generate_messages_nodejs)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS gpio_control_generate_messages_nodejs)

### Section generating for lang: genpy
### Generating Messages
_generate_msg_py(gpio_control
  "/home/thattori/capstone/velma/src/gpio/msg/InputState.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/gpio_control
)
_generate_msg_py(gpio_control
  "/home/thattori/capstone/velma/src/gpio/msg/OutputState.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/gpio_control
)

### Generating Services

### Generating Module File
_generate_module_py(gpio_control
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/gpio_control
  "${ALL_GEN_OUTPUT_FILES_py}"
)

add_custom_target(gpio_control_generate_messages_py
  DEPENDS ${ALL_GEN_OUTPUT_FILES_py}
)
add_dependencies(gpio_control_generate_messages gpio_control_generate_messages_py)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/thattori/capstone/velma/src/gpio/msg/InputState.msg" NAME_WE)
add_dependencies(gpio_control_generate_messages_py _gpio_control_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/thattori/capstone/velma/src/gpio/msg/OutputState.msg" NAME_WE)
add_dependencies(gpio_control_generate_messages_py _gpio_control_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(gpio_control_genpy)
add_dependencies(gpio_control_genpy gpio_control_generate_messages_py)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS gpio_control_generate_messages_py)



if(gencpp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/gpio_control)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/gpio_control
    DESTINATION ${gencpp_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_cpp)
  add_dependencies(gpio_control_generate_messages_cpp std_msgs_generate_messages_cpp)
endif()

if(geneus_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/gpio_control)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/gpio_control
    DESTINATION ${geneus_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_eus)
  add_dependencies(gpio_control_generate_messages_eus std_msgs_generate_messages_eus)
endif()

if(genlisp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/gpio_control)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/gpio_control
    DESTINATION ${genlisp_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_lisp)
  add_dependencies(gpio_control_generate_messages_lisp std_msgs_generate_messages_lisp)
endif()

if(gennodejs_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/gpio_control)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/gpio_control
    DESTINATION ${gennodejs_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_nodejs)
  add_dependencies(gpio_control_generate_messages_nodejs std_msgs_generate_messages_nodejs)
endif()

if(genpy_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/gpio_control)
  install(CODE "execute_process(COMMAND \"/usr/bin/python3\" -m compileall \"${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/gpio_control\")")
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/gpio_control
    DESTINATION ${genpy_INSTALL_DIR}
    # skip all init files
    PATTERN "__init__.py" EXCLUDE
    PATTERN "__init__.pyc" EXCLUDE
  )
  # install init files which are not in the root folder of the generated code
  string(REGEX REPLACE "([][+.*()^])" "\\\\\\1" ESCAPED_PATH "${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/gpio_control")
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/gpio_control
    DESTINATION ${genpy_INSTALL_DIR}
    FILES_MATCHING
    REGEX "${ESCAPED_PATH}/.+/__init__.pyc?$"
  )
endif()
if(TARGET std_msgs_generate_messages_py)
  add_dependencies(gpio_control_generate_messages_py std_msgs_generate_messages_py)
endif()
