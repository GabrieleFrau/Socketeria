#ifndef XSOCKET_DEFINES_HPP_INCLUDED
#define XSCOKET_DEFINES_HPP_INCLUDED
    #if defined(__APPLE__) || defined(__unix__)
        #define SOCKET_ERROR -1
        #define INVALID_SOCKET -1
    #endif
    #ifdef _WIN32
        #define ISWINZ
		#undef UNICODE
    #endif
        #define BUFFER_SIZE 4096
        #define BUFFER_PACKET_MAX_SIZE (BUFFER_SIZE - 1)
#endif
