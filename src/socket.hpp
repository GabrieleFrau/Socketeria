#ifndef SOCKET_HPP_INCLUDED
#define SOCKET_HPP_INCLUDED
#include "interface.hpp"
#include "defines.hpp"
#include "types.hpp"
#include <vector>
#include <array>
#include <string>
#if defined(__unix__) || defined(__APPLE__)
#include <unistd.h>
#endif
using namespace nSocket;
using namespace nAddress;

class Socket : protected ISocket, protected IAddress
{
public:
	Socket() = delete;
    Socket(Family _family, Type _type, Protocol _protocol);
    Socket(addr_IPvX* _address, in_port_t _port, Type _type, Protocol _protocol);
    Socket(addr_IPv4* _address, Type _type, Protocol _protocol);
    Socket(addr_IPv6* _address, Type _type, Protocol _protocol);
    Socket(std::string _ip, int _port, Type _type, Protocol _protocol, Family _family, bool _autobind);
    virtual ~Socket();

    TCPSenderInfo			Accept();
    bool                    Bind(addr_IPvX* _addr);
    bool                    Bind(addr_IPvX* _addr, int _addrlen);
    void                    Close();
    void                    Create(Family _family, Type _type);
    std::string             GetIP(addr_IPvX* _address);
    std::string             GetIP(addr_IPv4* _address);
    std::string             GetIP(addr_IPv6* _address);
    int                     GetPort(addr_IPvX* _address);
    int                     GetPort(addr_IPv4* _address);
    int                     GetPort(addr_IPv6* _address);
    virtual bool            IsBound();
    void                    ShutDown();
    std::vector<NPAddrInfo> GetAddresses(std::string _ip,
                                        int _port,
                                        Type _type,
                                        Protocol _protocol,
                                        Family _family = Family::Unspecified);
protected:
    void                    Create();
#ifdef _WIN32
    void                    InitWSA();
    bool					m_isWsaStarted = false;
#endif
    SOCKET					m_sockId = INVALID_SOCKET;
    bool					m_isBound = false;
    std::vector<NPAddrInfo> m_addresses;
    Family					m_family;
    Type					m_type;
    Protocol				m_protocol;
};
#endif // Socket_HPP
