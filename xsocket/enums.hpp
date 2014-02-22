#ifndef XSOCKET_ENUMS_HPP_INCLUDED
#define XSOCKET_ENUMS_HPP_INCLUDED
#ifdef __unix__
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#endif
#ifdef _WIN32
		#undef WINVER
		#undef _WIN32_WINNT
		#undef NTDDI_VERSION
		#define NTDDI_VERSION NTDDI_VISTASP2
		#define WINVER _WIN32_WINNT_VISTASP2
		#define _WIN32_WINNT _WIN32_WINNT_VISTA
#include <winsock2.h>
#include <ws2tcpip.h>
#endif
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
namespace nAddress
{
    enum class Family : int {
    Unspecified = AF_UNSPEC,
    IPv4 = AF_INET,
    IPv6 = AF_INET6
    };
}
#endif
