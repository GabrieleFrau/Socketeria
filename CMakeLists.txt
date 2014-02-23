cmake_minimum_required (VERSION 2.6)
project (Socketeria)

set (SOCKETERIA_VERSION_MAJOR 0)
set (SOCKETERIA_VERSION_MINOR 5)
set	(SOCKETERIA_VERSION_PATCH 0)
set	(SOCKETERIA_VERSION_EXTRA 0)
set	(SOCKETERIA_VERSION "${SOCKETERIA_VERSION_MAJOR}.${SOCKETERIA_VERSION_MINOR}")
set	(SOCKETERIA_VERSION_FULL "${SOCKETERIA_VERSION}_${SOCKETERIA_VERSION_PATCH}")
set 	(CMAKE_BUILD_TYPE Debug)
if(NOT MSVC)
	set	(CMAKE_CXX_FLAGS_DEBUG -std=c++11)
else()
	set (CMAKE_CXX_FLAGS_DEBUG "/D_CRT_SECURE_NO_WARNINGS")
endif()
option (SOCKETERIA_BUILD_DOCS "use doxygen to build the project documentation" OFF)

configure_file (
  "${PROJECT_SOURCE_DIR}/socketeriaConfig.h.in"
  "${PROJECT_BINARY_DIR}/socketeriaConfig.h"
)
find_package(Doxygen)
if (DOXYGEN_FOUND AND SOCKETERIA_BUILD_DOCS)
	add_subdirectory(docs)
	configure_file(
	"${PROJECT_SOURCE_DIR}/docs/Doxyfile.in"
    "${PROJECT_BINARY_DIR}/docs/Doxyfile" @ONLY
)
endif()

add_subdirectory (xsocket)

include_directories ("${PROJECT_BINARY_DIR}")
include_directories ("${PROJECT_SOURCE_DIR}/xsocket")

link_directories ("${PROJECT_BINARY_DIR}/xsocket")

add_executable (socketeria main.cpp)
target_link_libraries (socketeria xsocket)
if(WIN32)
  target_link_libraries(socketeria wsock32 ws2_32)
endif()
