#ifndef SOCKET_TYPES_HPP_INCLUDED
#define SOCKET_TYPES_HPP_INCLUDED
#include "defines.hpp"
#ifdef ISUNIX
typedef int SOCKET;
#endif
#ifdef ISWINZ
typedef unsigned int SOCKET;
typedef int socklen_t;
typedef int in_port_t;
#endif
typedef struct sockaddr_in addr_IPv4;
typedef struct sockaddr_in6 addr_IPv6;
typedef struct sockaddr_storage addr_storage;
typedef struct sockaddr addr_IPvX;
typedef struct addrinfo addr_info;

typedef struct sUDPSenderInfo
{
    addr_storage* sender;
    std::string buffer;
}UDPsenderInfo;
typedef struct sTCPSenderInfo
{
    addr_storage* sender;
    socklen_t senderlen;
    int id;
}TCPsenderInfo;
typedef struct sNPAddrInfo
{
	int ai_flags;
	int ai_family;
	int ai_socktype;
	int ai_protocol;
	socklen_t ai_addrlen;
	#ifdef ISUNIX
	struct sockaddr *ai_addr;
	char* ai_canonname;
	#endif
	#ifdef ISWINZ
	char* ai_canonname;
	struct sockaddr *ai_addr;
	#endif //idiots
}npAddrInfo;
#endif