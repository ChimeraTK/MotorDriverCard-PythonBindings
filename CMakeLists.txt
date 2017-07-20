cmake_minimum_required(VERSION 2.8.0)

project(ChimeraTK-steppermotor-py)

set(${PROJECT_NAME}_MAJOR_VERSION 00)
set(${PROJECT_NAME}_MINOR_VERSION 03)
set(${PROJECT_NAME}_PATCH_VERSION 02)
set(${PROJECT_NAME}_VERSION
  ${${PROJECT_NAME}_MAJOR_VERSION}.${${PROJECT_NAME}_MINOR_VERSION}.${${PROJECT_NAME}_PATCH_VERSION})
set(${PROJECT_NAME}_SOVERSION ${${PROJECT_NAME}_MAJOR_VERSION}.${${PROJECT_NAME}_MINOR_VERSION})

FIND_PACKAGE(mtca4u-MotorDriverCard 00.12 REQUIRED)
include_directories(${mtca4u-MotorDriverCard_INCLUDE_DIRS})
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${mtca4u-MotorDriverCard_CXX_FLAGS}")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wshadow -pedantic -Wuninitialized")
set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -Wl,--export-dynamic")
message("CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS}")
message("mtca4u-MotorDriverCard_CXX_FLAGS ${mtca4u-MotorDriverCard_CXX_FLAGS}")

FIND_PACKAGE(Boost COMPONENTS python REQUIRED)
include_directories( ${Boost_INCLUDE_DIR} )
FIND_PACKAGE(PythonLibs REQUIRED 2)
include_directories( ${PYTHON_INCLUDE_DIRS} )

#message("\${Boost_LIBRARIES} ${Boost_LIBRARIES}")
#message("\${PYTHON_LIBRARIES} ${PYTHON_LIBRARIES}")
#message("\${PYTHON_INCLUDE_DIRS} ${PYTHON_INCLUDE_DIRS}")

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
install(TARGETS ${MAIN_TARGET} LIBRARY DESTINATION lib/python2.7/dist-packages/ChimeraTK)
install(FILES __init__.py DESTINATION lib/python2.7/dist-packages/ChimeraTK)

######### TESTING ###########
#copy the test files
file(GLOB TEST_FILES  tests/*.py)
file(COPY ${TEST_FILES} DESTINATION ${CMAKE_BINARY_DIR})

#add them to ctest
enable_testing()
foreach( testFile  ${TEST_FILES})
  #NAME_WE means the base name without path and (longest) extension
  get_filename_component(testName ${testFile} NAME_WE)
  add_test(${testName} ${testName}.py)
endforeach()
