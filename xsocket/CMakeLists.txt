add_subdirectory (xplatform)
link_directories ("${XSOCKET_BINARY_DIR}/xsocket")
add_library (xsocket STATIC socket.cpp sockettcp.cpp socketudp.cpp)
target_link_libraries(xsocket xplatform)