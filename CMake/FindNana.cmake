

set(NANA_FOUND FALSE)

find_path(
	NANA_INCLUDE_DIR
	nana/gui.hpp
	PATH_SUFFIXES
		include
	PATHS
		/usr
		/usr/local
		${NANA_DIR}
		${NANA_ROOT}
		$ENV{NANA_DIR}
		$ENV{NANA_ROOT}
)

find_library(
	NANA_LIBRARY_RELEASE
	nana
	PATH_SUFFIXES
		Release
	PATHS
		/usr/lib
		/usr/local/lib
		${NANA_DIR}/lib
		${NANA_ROOT}/lib
		$ENV{NANA_DIR}/lib
		$ENV{NANA_ROOT}/lib
)

find_library(
	NANA_LIBRARY_DEBUG
	nana_d
	PATH_SUFFIXES
        Debug
	PATHS
		/usr/lib
		/usr/local/lib
		${NANA_DIR}/lib
		${NANA_ROOT}/lib
		$ENV{NANA_DIR}/lib
		$ENV{NANA_ROOT}/lib
)

if(NANA_LIBRARY_RELEASE AND NANA_LIBRARY_DEBUG)
	set(NANA_LIBRARY debug ${NANA_LIBRARY_DEBUG} optimized ${NANA_LIBRARY_RELEASE})
endif()

if(NANA_LIBRARY_RELEASE AND NOT NANA_LIBRARY_DEBUG)
	set(NANA_LIBRARY_DEBUG ${NANA_LIBRARY_RELEASE})
	set(NANA_LIBRARY ${NANA_LIBRARY_RELEASE})
endif()

if(NANA_LIBRARY_DEBUG AND NOT NANA_LIBRARY_RELEASE)
	set(NANA_LIBRARY_RELEASE ${NANA_LIBRARY_DEBUG})
	set(NANA_LIBRARY ${NANA_LIBRARY_DEBUG})
endif()

if(NOT NANA_INCLUDE_DIR OR NOT NANA_LIBRARY)
	message("nana include dir: ${NANA_INCLUDE_DIR}")
	message("nana library: ${NANA_LIBRARY}")
	if(Nana_FIND_REQUIRED)
		message(FATAL_ERROR "nana not found.")
	elseif(NOT NANA_FIND_QUIETLY)
		message("nana not found.")
	endif()
else()
	set(NANA_FOUND true)
	if (NOT NANA_FIND_QUIETLY)
		message(STATUS "nana found: ${NANA_INCLUDE_DIR}")
	endif()
endif()
