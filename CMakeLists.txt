cmake_minimum_required(VERSION 3.0)

project("statModel" C CXX)


# Ensure that we have a C++11 compiler.
include(CMake/CXX11.cmake)
check_for_cxx11_compiler(HAS_CXX11)
if(NOT HAS_CXX11)
  message(FATAL_ERROR "No C++11 compiler available!")
endif(NOT HAS_CXX11)
enable_cxx11()

# Include modules in the CMake directory.
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/CMake")

include(CMake/FindChaoWangCppUtil.cmake)
#find_package(chaoWangCppUtil REQUIRED)
if(chaoWangCppUtil_FOUND)
	include_directories(${chaoWangCppUtil_INCLUDE_DIRS})
	link_directories(${chaoWangCppUtil_LIBRARIES})
	add_definitions(-DchaoWangCppUtil_FOUND)
endif(chaoWangCppUtil_FOUND)


include_directories(${CMAKE_SOURCE_DIR})
# Recurse into the rest of the project.
add_subdirectory(src/${PROJECT_NAME})


