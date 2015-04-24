# - Find NLopt
# Find the native NLopt includes and library
#
#  chaoWangCppUtil_INCLUDE_DIR - where to find chaoWangCppUtil.h, etc.
#  chaoWangCppUtil_LIBRARIES   - List of libraries when using chaoWangCppUtil.
#  chaoWangCppUtil_FOUND       - True if chaoWangCppUtil found.


IF (chaoWangCppUtil_INCLUDE_DIR)
  # Already in cache, be silent
  SET (chaoWangCppUtil_FIND_QUIETLY TRUE)
ENDIF (chaoWangCppUtil_INCLUDE_DIR)

FIND_PATH(chaoWangCppUtil_INCLUDE_DIR chaoWangCppUtil.hpp
	/usr/local/include/chaoWangCppUtil)

SET (chaoWangCppUtil_NAMES chaoWangCppUtil)
FIND_LIBRARY (chaoWangCppUtil_LIBRARY NAMES ${chaoWangCppUtil_NAMES})

# handle the QUIETLY and REQUIRED arguments and set chaoWangCppUtil_FOUND to TRUE if 
# all listed variables are TRUE
INCLUDE (FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS (chaoWangCppUtil DEFAULT_MSG 
  chaoWangCppUtil_LIBRARY 
  chaoWangCppUtil_INCLUDE_DIR)

IF(chaoWangCppUtil_FOUND)
  SET (chaoWangCppUtil_LIBRARIES ${chaoWangCppUtil_LIBRARY})
ELSE (chaoWangCppUtil_FOUND)
  SET (chaoWangCppUtil_LIBRARIES)
ENDIF (chaoWangCppUtil_FOUND)

MARK_AS_ADVANCED (chaoWangCppUtil_LIBRARY chaoWangCppUtil_INCLUDE_DIR)

