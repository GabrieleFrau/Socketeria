#ifndef ENUMS_HPP_INCLUDED
#define ENUMS_HPP_INCLUDED
#if defined(__APPLE__) || defined(__unix__)
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#define SOCKET_ERROR -1
#define INVALID_SOCKET -1
#endif
#ifdef _WIN32
		#undef UNICODE
		#undef WINVER
		#undef _WIN32_WINNT
		#undef NTDDI_VERSION
		#define NTDDI_VERSION NTDDI_VISTA
		#define WINVER _WIN32_WINNT_VISTA
		#define _WIN32_WINNT _WIN32_WINNT_VISTA
    #include <winsock2.h>
    #include <ws2tcpip.h>
#endif
namespace Address
{
    enum class Family : int {
    Unspecified = AF_UNSPEC,
    IPv4 = AF_INET,
    IPv6 = AF_INET6
    };
}
namespace nSocket
{
	enum class Type : int{
		Datagram = SOCK_DGRAM,
		Stream = SOCK_STREAM
	};
	enum class Protocol : int {
		TCP = IPPROTO_TCP,
		UDP = IPPROTO_UDP
	};
}
#endif
