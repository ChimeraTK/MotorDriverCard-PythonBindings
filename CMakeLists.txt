cmake_minimum_required(VERSION 2.8.0)

project(mtca4u_MotorDriverCardPython)

set(${PROJECT_NAME}_MAJOR_VERSION 00)
set(${PROJECT_NAME}_MINOR_VERSION 00)
set(${PROJECT_NAME}_PATCH_VERSION 00)
set(${PROJECT_NAME}_VERSION
  ${${PROJECT_NAME}_MAJOR_VERSION}.${${PROJECT_NAME}_MINOR_VERSION}.${${PROJECT_NAME}_PATCH_VERSION})
set(${PROJECT_NAME}_SOVERSION ${${PROJECT_NAME}_MAJOR_VERSION}.${${PROJECT_NAME}_MINOR_VERSION})

FIND_PACKAGE(MotorDriverCard 00.04 REQUIRED)
include_directories(${MotorDriverCard_INCLUDE_DIRS})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wshadow -pedantic -Wuninitialized")
set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -Wl,--export-dynamic")

FIND_PACKAGE(Boost COMPONENTS python REQUIRED)
include_directories( ${Boost_INCLUDE_DIR} )
FIND_PACKAGE(PythonLibs REQUIRED)
include_directories( ${PYTHON_INCLUDE_DIRS} )

#message("\${Boost_LIBRARIES} ${Boost_LIBRARIES}")
#message("\${PYTHON_LIBRARIES} ${PYTHON_LIBRARIES}")
#message("\${PYTHON_INCLUDE_DIRS} ${PYTHON_INCLUDE_DIRS}")

add_library(${PROJECT_NAME} SHARED MotorDriverCardPython.cc )
target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES} ${PYTHON_LIBRARIES}
				      ${MotorDriverCard_LIBRARIES})
#turn off the lib prefix for the python module 
#otherwise the module would be called "libSomething" instead of just "Something"
set_target_properties(${PROJECT_NAME} PROPERTIES PREFIX "")
