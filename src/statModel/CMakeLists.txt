include_directories(..)

# Add summary to list of sources.
#set(${PROJECT_NAME}_SRCS ${"${PROJECT_NAME}_SRCS"} "${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}.hpp")
set(STATMODEL_SRCS ${STATMODEL_SRCS} "${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}.hpp")

set(DIRS
	statModelCore
	models)

foreach(dir ${DIRS})
    add_subdirectory(${dir})
endforeach()

get_cmake_property(_variableNames VARIABLES)
foreach (_variableName ${_variableNames})
    message(STATUS "${_variableName}=${${_variableName}}")
endforeach()

add_library(${PROJECT_NAME} SHARED ${STATMODEL_SRCS})
#add_library(${PROJECT_NAME} SHARED ${${PROJECT_NAME}_SRCS})

target_link_libraries(${PROJECT_NAME}
	chaoWangCppUtil
	)



set_target_properties(statModel
	PROPERTIES
	VERSION 0.1
	SOVERSION 1
	)

# Make sure the linker can find the needed library.
# rt: clock_gettime()
if(UNIX AND NOT APPLE)
    target_link_libraries(statModel rt)
endif(UNIX AND NOT APPLE)



# Collect all header files in the library.
file(GLOB_RECURSE INCLUDE_H_FILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.h)
file(GLOB_RECURSE INCLUDE_HPP_FILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.hpp)
set(INCLUDE_FILES ${INCLUDE_H_FILES} ${INCLUDE_HPP_FILES})

# Move all of these header files to <builddir>/include/chaoWangCppUtil/ after the library
# is built.  First we have to create that directory though.
add_custom_target(statModel_headers)
add_custom_command(TARGET statModel_headers POST_BUILD
	COMMENT "Moving header files to include/statModel/"
  COMMAND ${CMAKE_COMMAND} ARGS -E
    make_directory ${CMAKE_BINARY_DIR}/include/statModel/)


# Then copy each of the header files over to that directory.
foreach(incl_file ${INCLUDE_FILES})
	add_custom_command(TARGET ${PROJECT_NAME}_headers POST_BUILD
    COMMAND ${CMAKE_COMMAND} ARGS -E
      copy ${CMAKE_CURRENT_SOURCE_DIR}/${incl_file}
			${CMAKE_BINARY_DIR}/include/${PROJECT_NAME}/${incl_file})
endforeach()

# At install time, we simply install that directory of header files we
# collected to include/.
install(DIRECTORY ${CMAKE_BINARY_DIR}/include/${PROJECT_NAME} DESTINATION
	include)

# Set generated executables to be installed.  Unfortunately they must manually
# be entered...
install(TARGETS ${PROJECT_NAME} 
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
	)

add_dependencies(${PROJECT_NAME} ${PROJECT_NAME}_headers)

# For 'make test'.
#add_custom_target(test
#	${CMAKE_BINARY_DIR}/bin/chaoWangCppUtil_test "--log_level=test_suite" # Set UTF runtime param
#  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/ # This is where test files are put.
#	COMMENT "Running CHAO_WANG_CPP_UTIL test"
#	DEPENDS chaoWangCppUtil_test)

