cmake_minimum_required (VERSION 2.6)
project (Socketeria CXX)

option (SOCKETERIA_BUILD_DOCS "use doxygen to build the project documentation" OFF)
option (SOCKETERIA_BUILD_EXAMPLE "build a test program to try the lib out" ON)

find_package(Doxygen)

if (DOXYGEN_FOUND AND SOCKETERIA_BUILD_DOCS)
	add_subdirectory(docs)
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
	${PROJECT_SOURCE_DIR}/src/enums.hpp
	${PROJECT_SOURCE_DIR}/src/types.hpp
)

set(CMAKE_BUILD_TYPE Debug)

if(MINGW OR CMAKE_COMPILER_IS_GNUCXX)
	message(WARNING "You're using a compiler that does not have a complete c++11 implementation")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
endif()
if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
	message(STATUS "Changing library from libstdc++ to libc++")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -stdlib=libc++")
endif()
if(SOCKETERIA_BUILD_EXAMPLE)
	add_subdirectory(example)
endif()

add_library (xsocket STATIC ${SOURCES} ${HEADERS})
if(WIN32)
	target_link_libraries(xsocket wsock32 ws2_32)
endif()




