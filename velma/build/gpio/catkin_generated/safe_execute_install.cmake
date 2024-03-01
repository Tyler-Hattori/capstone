execute_process(COMMAND "/home/ubuntu/F1Tenth/velma/build/gpio/catkin_generated/python_distutils_install.sh" RESULT_VARIABLE res)

if(NOT res EQUAL 0)
  message(FATAL_ERROR "execute_process(/home/ubuntu/F1Tenth/velma/build/gpio/catkin_generated/python_distutils_install.sh) returned error code ")
endif()
