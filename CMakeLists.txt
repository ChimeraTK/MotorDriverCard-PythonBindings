cmake_minimum_required(VERSION 2.8.0)
project(ChimeraTK-steppermotor-py)


#
# cmake/Modules has function defenitions we use
list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/Modules)
include(genericFunctions)

#
# Define cache option PYTHON3 to indicate if python3 compilation is required;
# else we compile for python 2
set(PYTHON3 FALSE CACHE BOOL
          "Builds modules for python3 if true and python2 if false") 
#
# Unfortunately cmake version on trusty needs to locate PythonLibs for python3.
# There is also a bug with cmake where having this causes find_package to always
# return the python3 libraries even when python 2 libraries are specified . For
# this reason set this variable only on python3 builds.
if(PYTHON3)
  set(Python_ADDITIONAL_VERSIONS 3.4)
endif()

#
# Decide on the python major version to use based on the cache variable PYTHON3:
if(PYTHON3)
  set(python_major_version "3")
else()
  set(python_major_version "2")
endif()

set(${PROJECT_NAME}_MAJOR_VERSION 00)
set(${PROJECT_NAME}_MINOR_VERSION 03)
set(${PROJECT_NAME}_PATCH_VERSION 03)
set(${PROJECT_NAME}_VERSION
  ${${PROJECT_NAME}_MAJOR_VERSION}.${${PROJECT_NAME}_MINOR_VERSION}.${${PROJECT_NAME}_PATCH_VERSION})
set(${PROJECT_NAME}_SOVERSION ${${PROJECT_NAME}_MAJOR_VERSION}.${${PROJECT_NAME}_MINOR_VERSION})

find_package(mtca4u-MotorDriverCard 01.07 REQUIRED)
find_package(PythonLibs ${python_major_version} REQUIRED)
find_package(PythonInterp ${python_major_version} REQUIRED)
get_boost_python_component_name(PYTHONLIBS_VERSION_STRING boost_python)
find_package(Boost COMPONENTS ${boost_python} REQUIRED)


include_directories(${mtca4u-MotorDriverCard_INCLUDE_DIRS})
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${mtca4u-MotorDriverCard_CXX_FLAGS}")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wshadow -pedantic -Wuninitialized")
set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -Wl,--export-dynamic")

include_directories( ${Boost_INCLUDE_DIR} )
include_directories( ${PYTHON_INCLUDE_DIRS} )

#The -py is redundant for a python module, and the ChimeraTK will be
#a directory with multiple we will libraries
set(MAIN_TARGET "steppermotor")
add_library(${MAIN_TARGET} SHARED MotorDriverCardPython.cc )
target_link_libraries(${MAIN_TARGET} ${Boost_LIBRARIES} ${PYTHON_LIBRARIES}
				      ${mtca4u-MotorDriverCard_LIBRARIES})
#turn off the lib prefix for the python module 
#otherwise the module would be called "libSomething" instead of just "Something"
set_target_properties(${MAIN_TARGET} PROPERTIES PREFIX "")

set_property(TARGET ${MAIN_TARGET} PROPERTY INSTALL_RPATH_USE_LINK_PATH TRUE)

get_python_module_install_path(PYTHONLIBS_VERSION_STRING install_path)
set(install_path "${install_path}/ChimeraTk")
message(STATUS "Install Path: ${install_path}")

install(TARGETS ${MAIN_TARGET} LIBRARY DESTINATION ${install_path})
install(FILES __init__.py DESTINATION ${install_path})

######### TESTING ###########
#copy the test files
configure_file(tests/test_import.py.in test_import.py)
file(COPY tests/devices.dmap DESTINATION ${CMAKE_BINARY_DIR})
set(TEST_FILES "test_import.py")

#add them to ctest
enable_testing()
foreach( testFile  ${TEST_FILES})
  #NAME_WE means the base name without path and (longest) extension
  get_filename_component(testName ${testFile} NAME_WE)
  add_test(${testName} ${testName}.py)
endforeach()

