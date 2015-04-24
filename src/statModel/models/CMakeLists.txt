include_directories(..)

# Add summary to list of sources.
set(${PROJECT_NAME}_SRCS ${PROJECT_NAME}_SRCS} "${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}.hpp")

set(DIRS
	reducedRankRegression
	)

foreach(dir ${DIRS})
    add_subdirectory(${dir})
endforeach()

set(STATMODEL_SRCS ${STATMODEL_SRCS} ${DIR_SRCS} PARENT_SCOPE)
