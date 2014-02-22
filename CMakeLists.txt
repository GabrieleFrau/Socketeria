cmake_minimum_required (VERSION 2.6)
project (SOCKETERIA)

set (SOCKETERIA_VERSION_MAJOR 0)
set (SOCKETERIA_VERSION_MINOR 5)
set	(SOCKETERIA_VERSION_PATCH 0)
set	(SOCKETERIA_VERSION_EXTRA 0)
set	(SOCKETERIA_VERSION "${SOCKETERIA_VERSION_MAJOR}.${SOCKETERIA_VERSION_MINOR}")
set	(SOCKETERIA_VERSION_FULL "${SOCKETERIA_VERSION}.${SOCKETERIA_VERSION_PATCH}${SOCKETERIA_VERSION_EXTRA}")
set 	(CMAKE_BUILD_TYPE Debug)
set	(CMAKE_CXX_FLAGS_DEBUG -std=c++11)
option (SOCKETERIA_BUILD_DOCS "use doxygen to build the project documentation" OFF)

configure_file (
  "${PROJECT_SOURCE_DIR}/socketeriaConfig.h.in"
  "${PROJECT_BINARY_DIR}/socketeriaConfig.h"
)
find_package(Doxygen)
if (DOXYGEN_FOUND AND SOCKETERIA_BUILD_DOCS)
	add_subdirectory(docs)
	configure_file(
	${SOCKETERIA_SOURCE_DIR}/docs/Doxyfile.in
    ${SOCKETERIA_BINARY_DIR}/docs/Doxyfile @ONLY
)
endif()

add_subdirectory (xsocket)

include_directories (${PROJECT_BINARY_DIR})
include_directories ("${PROJECT_SOURCE_DIR}/xsocket")

link_directories ("${PROJECT_BINARY_DIR}/xsocket")

add_executable (socketeria main.cpp)
target_link_libraries (socketeria xsocket)
