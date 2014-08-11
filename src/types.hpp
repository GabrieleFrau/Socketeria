#ifndef TYPES_HPP_INCLUDED
#define TYPES_HPP_INCLUDED
#include "enums.hpp"
#include <memory>
#include <vector>
#if defined(__unix__) || defined(__APPLE__)
#include <netdb.h>
#include <cstring>
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
	UDPSenderInfo()
		: senderlen(sizeof(addr_storage))
	{
		memset(&sender, 0, sizeof(addr_storage));
	}
	~UDPSenderInfo() = default;
    addr_storage sender;
	socklen_t senderlen;
    std::string buffer;
};
class TCPSenderInfo
{
public:
	TCPSenderInfo()
		: senderlen(sizeof(addr_storage))
		, id(0)
	{
		memset(&sender, 0, sizeof(addr_storage));
	}
	~TCPSenderInfo() = default;
    addr_storage sender;
    socklen_t senderlen;
    SOCKET id;
};

class NPAddrInfo
{
public:
	NPAddrInfo() = default;
	NPAddrInfo(addr_info& info)
	{
		ai_flags = info.ai_flags;
		ai_family = static_cast<Address::Family>(info.ai_family);
		ai_socktype = static_cast<nSocket::Type>(info.ai_socktype);
		ai_protocol = static_cast<nSocket::Protocol>(info.ai_protocol);
		ai_addrlen = info.ai_addrlen;
		ai_addr = *(info.ai_addr);
		ai_canonname = info.ai_canonname != nullptr ? info.ai_canonname : "\0";
	}
	~NPAddrInfo() = default;
	std::string				ToString()
	{
		std::string tmp;
		tmp = ((ai_family != Address::Family::Unspecified) ? ((ai_family == Address::Family::IPv4) ? ("IPv4") : ("IPv6")) : ("Unspecified"));
		tmp += " ";
		tmp += ((ai_socktype == nSocket::Type::Datagram) ? ("Datagram") : ("Stream"));
		tmp += " ";
		tmp += ((ai_protocol == nSocket::Protocol::UDP) ? ("UDP") : ("TCP"));
		tmp += " ";
		tmp += GetIP(ai_addr);
		return tmp;
	}
	static std::string      GetIP(addr_IPvX& _address)
	{
		long unsigned int length = (_address.sa_family == AF_INET) ? INET_ADDRSTRLEN : INET6_ADDRSTRLEN;
		std::vector<char> ip(length);
#if defined(__unix__) || defined(__APPLE__)
		inet_ntop(_address.sa_family, _address.sa_data, ip.data(), length);
#endif
#ifdef _WIN32
		if (WSAAddressToString(&_address, length, NULL, ip.data(), &length) == SOCKET_ERROR)
		{
			char tmp[256];
			strerror_s(tmp, errno);
			throw tmp;
		}
#endif
		return std::string(ip.data());
	}
	static std::string      GetIP(addr_IPv4& _address)
	{
		return GetIP(reinterpret_cast<addr_IPvX&>(_address));
	}
	static std::string      GetIP(addr_IPv6& _address)
	{
		return GetIP(reinterpret_cast<addr_IPvX&>(_address));
	}
	static int              GetPort(addr_IPvX& _address)
	{
		return (_address.sa_family == AF_INET)
			? GetPort(reinterpret_cast<addr_IPv4&>(_address))
			: GetPort(reinterpret_cast<addr_IPv6&>(_address));
	}
	static int              GetPort(addr_IPv4& _address)
	{
		return htons(_address.sin_port);
	}
	static int				GetPort(addr_IPv6& _address)
	{
		return htons(_address.sin6_port);
	}

	int ai_flags;
	Address::Family ai_family;
	nSocket::Type ai_socktype;
	nSocket::Protocol ai_protocol;
	socklen_t ai_addrlen;
	#if defined(__unix__) || defined(__APPLE__)
	struct sockaddr ai_addr;
	std::string ai_canonname;
	#endif
	#ifdef _WIN32
	std::string ai_canonname;
	struct sockaddr ai_addr;
	#endif //idiots
};
#endif
