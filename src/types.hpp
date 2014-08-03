#ifndef TYPES_HPP_INCLUDED
#define TYPES_HPP_INCLUDED
#include "defines.hpp"
#if defined(__unix__) || defined(__APPLE__)
#include <netdb.h>	// 
    typedef int SOCKET;
#endif
#ifdef _WIN32
typedef int socklen_t;
typedef int in_port_t;
typedef int ssize_t;
#endif
typedef struct sockaddr_in addr_IPv4;
typedef struct sockaddr_in6 addr_IPv6;
typedef struct sockaddr_storage addr_storage;
typedef struct sockaddr addr_IPvX;
typedef struct addrinfo addr_info;

class UDPSenderInfo
{
public:
    addr_storage sender;
    std::string buffer;
};
class TCPSenderInfo
{
public:
	TCPSenderInfo() : senderlen(0), id(0) {}
    addr_storage sender;
    socklen_t senderlen;
    SOCKET id;
};

class NPAddrInfo
{
public:
	NPAddrInfo() = delete;
	NPAddrInfo(addr_info* info)
	{
		ai_flags = info->ai_flags;
		ai_family = info->ai_family;
		ai_socktype = info->ai_socktype;
		ai_protocol = info->ai_protocol;
		ai_addrlen = info->ai_addrlen;
		ai_addr = *(info->ai_addr);
		ai_canonname = _strdup(info->ai_canonname);
	}
	~NPAddrInfo()
	{
		if (ai_canonname != nullptr)
			free(ai_canonname);
	}
	int ai_flags;
	int ai_family;
	int ai_socktype;
	int ai_protocol;
	socklen_t ai_addrlen;
	#if defined(__unix__) || defined(__APPLE__)
	struct sockaddr ai_addr;
	char* ai_canonname;
	#endif
	#ifdef _WIN32
	char* ai_canonname;
	struct sockaddr ai_addr;
	#endif //idiots
};
#endif
