#include "socket.hpp"
#if defined(_DEBUG) || defined(DEBUG)
#include <iostream>
#endif
Socket::Socket(Family _family, Type _type, Protocol _protocol) : m_bufferSize(4096)
{
    m_family = _family;
    m_type = _type;
    m_protocol = _protocol;
    m_isBound = false;
	m_isWsaStarted = false;
	m_sockId = INVALID_SOCKET;
#ifdef _WIN32
    InitWSA();
#endif
    Create();
}
Socket::Socket(addr_IPvX& _address, in_port_t _port, Type _type, Protocol _protocol)
	: Socket(static_cast<Family>(_address.sa_family), _type, _protocol)
{
}
Socket::Socket(addr_IPv4& _address, Type _type, Protocol _protocol)
	: Socket(reinterpret_cast<addr_IPvX&>(_address), _address.sin_port, _type, _protocol)
{
}
Socket::Socket(addr_IPv6& _address, Type _type, Protocol _protocol)
	: Socket(reinterpret_cast<addr_IPvX&>(_address), _address.sin6_port, _type, _protocol)
{
}
Socket::Socket(int _port, Type _type, Protocol _protocol, Family _family, bool _autobind) : Socket(_family, _type, _protocol)
{
	if (_autobind)
	{
		std::vector<NPAddrInfo> addresses = GetAddresses(NULL, _port, _type, _protocol, _family);
		for (auto& address : addresses)
			if (Bind(address.ai_addr, address.ai_addrlen))
			{
				m_address = address;
#if defined(_DEBUG) || defined (DEBUG)
				std::clog << m_address.ToString() << std::endl;
#endif
				break;
			}
	}
}
Socket::Socket(std::string _ip, int _port, Type _type, Protocol _protocol, Family _family, bool _autobind) : Socket(_family, _type, _protocol)
{
	if (_autobind)
	{
		std::vector<NPAddrInfo> addresses = GetAddresses(_ip.c_str(), _port, _type, _protocol, _family);
		for (auto& address : addresses)
			if (Bind(address.ai_addr, address.ai_addrlen))
			{
				m_address = address;
				std::clog << m_address.ToString() << std::endl;
				break;
			}
	}
}
Socket::~Socket()
{
#ifdef _WIN32
    if(m_isWsaStarted)
    {
        if(WSACleanup())
            std::cerr<<"errore";
        else
            m_isWsaStarted = false;
    }
#endif
    Close();
}
bool Socket::Bind(addr_IPvX& _addr)
{
	return Bind(_addr, (_addr.sa_family == AF_INET) ? INET_ADDRSTRLEN : INET6_ADDRSTRLEN);
}
bool Socket::Bind(addr_IPvX& _addr,int _addrlen)
{
    if(m_sockId == INVALID_SOCKET)
        throw "Socket is not valid";
    else
    {
		if (bind(m_sockId, &_addr, _addrlen) == SOCKET_ERROR)
		{
			throw WSAGetLastError();
			return m_isBound = false;
		}
        else
            return m_isBound = true;
    }
}
void Socket::Close()
{
    if(m_sockId != INVALID_SOCKET)
#if defined(__unix__) || defined(__APPLE__)
        close(m_sockId);
#endif
#ifdef _WIN32
		closesocket(m_sockId);
#endif
}
void Socket::Create(Family _family, Type _type)
{
    m_family = _family;
    m_type = _type;
    Create();
}
void Socket::Create()
{
	//m_sockId = WSASocket(static_cast<int>(m_family), static_cast<int>(m_type), static_cast<int>(m_protocol), NULL, 0, WSA_FLAG_OVERLAPPED);
    m_sockId = socket(static_cast<int>(m_family),static_cast<int>(m_type), static_cast<int>(m_protocol));
    if(m_sockId == INVALID_SOCKET)
        throw strerror(errno);
    #ifdef __unix__
    int optvalue = 1;
	int* optval = &optvalue;
	#endif
	#ifdef _WIN32
    const char* optval = "true";
    #endif
    if(setsockopt(m_sockId, SOL_SOCKET, SO_REUSEADDR, optval, sizeof(optval)))
        throw strerror(errno); 
}
std::vector<NPAddrInfo> Socket::GetAddresses(const char *_ip, int _port, Type _type, Protocol _protocol, Family _family)
{
    addr_info myAddrSpecs;
    addr_info* myAddrInfo;
    std::vector<NPAddrInfo> ret;
    memset(&myAddrSpecs, 0, sizeof(myAddrSpecs));
    myAddrSpecs.ai_family = static_cast<int>(_family);
    myAddrSpecs.ai_socktype = static_cast<int>(_type);
	myAddrSpecs.ai_flags = ((_family == Family::IPv6) ? AI_V4MAPPED : 0);
	myAddrSpecs.ai_flags |= AI_PASSIVE;
    myAddrSpecs.ai_protocol = static_cast<int>(_protocol);
	std::string port = std::to_string(_port);
    int n = getaddrinfo(_ip, port.c_str() , &myAddrSpecs, &myAddrInfo);
#if defined(__unix__) || defined(__APPLE__)
    if(n < 0)
#endif
#ifdef _WIN32
    if(n != 0)
#endif
    {
		std::cerr << gai_strerror(n);
    }
    else
    {
        ret.clear();
		for (addr_info* next = myAddrInfo; next != NULL; next = next->ai_next)
		{
			ret.emplace_back(NPAddrInfo(*next));
		}
    }
    freeaddrinfo(myAddrInfo);
    return ret;
}
bool Socket::IsBound()
{
    return m_isBound;
}
void Socket::ShutDown()
{
        if(m_sockId != INVALID_SOCKET)
        {
			if (shutdown(m_sockId, 2) == SOCKET_ERROR)
			{
#ifdef _WIN32
				throw strerror(errno);
				if (closesocket(m_sockId) == SOCKET_ERROR)
#endif
#if defined(__unix__) || defined(__APPLE__)
				if (close(m_sockId))

#endif
						throw strerror(errno);
			}
        }
}
#ifdef _WIN32
void Socket::InitWSA()
{
    WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2,2), &wsaData) != NO_ERROR)
	{
		m_isWsaStarted = false;
		char tmp[256];
		strerror_s(tmp,errno);
		throw tmp;
	}
    else m_isWsaStarted = true;
}
#endif
