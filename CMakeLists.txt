cmake_minimum_required (VERSION 2.6)
project (Socketeria CXX)

option (SOCKETERIA_BUILD_DOCS "use doxygen to build the project documentation" OFF)
option (SOCKETERIA_BUILD_EXAMPLE "build a test program to try the lib out" ON)

find_package(Doxygen)

if (DOXYGEN_FOUND AND SOCKETERIA_BUILD_DOCS)
	add_subdirectory(docs)
	configure_file(
	"${PROJECT_SOURCE_DIR}/docs/Doxyfile.in"
    "${PROJECT_BINARY_DIR}/docs/Doxyfile" @ONLY
)
endif()

include_directories("${PROJECT_SOURCE_DIR}/src")

set(SOURCES
	${PROJECT_SOURCE_DIR}/src/socket.cpp
	${PROJECT_SOURCE_DIR}/src/sockettcp.cpp
	${PROJECT_SOURCE_DIR}/src/socketudp.cpp
)
set(HEADERS
	${PROJECT_SOURCE_DIR}/src/socket.hpp
	${PROJECT_SOURCE_DIR}/src/sockettcp.hpp
	${PROJECT_SOURCE_DIR}/src/socketudp.hpp
	${PROJECT_SOURCE_DIR}/src/defines.hpp
	${PROJECT_SOURCE_DIR}/src/enums.hpp
	${PROJECT_SOURCE_DIR}/src/interface.hpp
	${PROJECT_SOURCE_DIR}/src/types.hpp
)

set(CMAKE_BUILD_TYPE Debug)

if(SOCKETERIA_BUILD_EXAMPLE)
	add_subdirectory(example)
endif()

add_library (xsocket STATIC ${SOURCES} ${HEADERS})
if(WIN32)
	target_link_libraries(xsocket wsock32 ws2_32)
endif()




