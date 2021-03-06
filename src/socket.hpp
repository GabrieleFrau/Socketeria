#ifndef SOCKET_HPP_INCLUDED
#define SOCKET_HPP_INCLUDED
#include "types.hpp"
#include <vector>
#include <array>
#include <string>
#if defined(_DEBUG) || defined(DEBUG)
#include <iostream>
#endif
#if defined(__unix__) || defined(__APPLE__)
#include <unistd.h>
#include <errno.h>
#endif
using namespace Address;
using namespace nSocket;
class Socket
{
public:
	Socket() = delete;
	Socket(const Socket&) = delete;
	Socket& operator=(const Socket&) = delete;
    Socket(Family _family, Type _type, Protocol _protocol);
    Socket(addr_IPvX& _address, in_port_t _port, Type _type, Protocol _protocol);
    Socket(addr_IPv4& _address, Type _type, Protocol _protocol);
    Socket(addr_IPv6& _address, Type _type, Protocol _protocol);
	Socket(in_port_t _port, Type _type, Protocol _protocol, Family _family, bool _autobind);
    Socket(std::string _ip, in_port_t _port, Type _type, Protocol _protocol, Family _family, bool _autobind);
    virtual ~Socket();

    TCPSenderInfo			Accept();
    bool                    Bind(addr_IPvX& _addr);
    bool                    Bind(addr_IPvX& _addr, socklen_t _addrlen);
    void                    Close();
    void                    Create(Family _family, Type _type);
    bool					IsBound();
    void                    ShutDown();
	void					SetBufferSize(size_t size);
protected:
	std::vector<NPAddrInfo> GetAddresses(const char* _ip,
                                        in_port_t _port,
                                        Type _type,
                                        Protocol _protocol,
                                        Family _family = Family::Unspecified);
    void                    Create();
#ifdef _WIN32
    void                    InitWSA();
    bool					m_isWsaStarted;
#endif
	size_t					m_bufferSize;
    SOCKET					m_sockId;
    bool					m_isBound;
	NPAddrInfo				m_address;
    Family					m_family;
    Type					m_type;
    Protocol				m_protocol;
};
#endif // Socket_HPP
