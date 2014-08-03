#include "socket.hpp"

Socket::Socket(Family _family, Type _type, Protocol _protocol)
{
#ifdef _WIN32
    InitWSA();
#endif
    m_family = _family;
    m_type = _type;
    m_protocol = _protocol;
    m_isBound = false;
    Create();
}
Socket::Socket(addr_IPvX* _address, in_port_t _port, Type _type, Protocol _protocol)
    : Socket((Family)_address->sa_family,_type,_protocol)
{
}
Socket::Socket(addr_IPv4* _address, Type _type, Protocol _protocol)
    : Socket((addr_IPvX*)_address,_address->sin_port,_type,_protocol)
{
}
Socket::Socket(addr_IPv6* _address, Type _type, Protocol _protocol)
    : Socket((addr_IPvX*)_address,_address->sin6_port,_type,_protocol)
{
}
Socket::Socket(std::string _ip, int _port,Type _type, Protocol _protocol, Family _family, bool _autobind = true) : Socket(_family,_type,_protocol)
{
    if(_autobind)
    {
        m_addresses = GetAddresses(_ip,_port,_type,_protocol,_family);
		for (auto& address : m_addresses)
			if (Bind(&address.ai_addr, address.ai_addrlen))
				break;
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
bool Socket::Bind(addr_IPvX* _addr)
{
	return Bind(_addr, (_addr->sa_family == AF_INET) ? INET_ADDRSTRLEN : INET6_ADDRSTRLEN);
}
bool Socket::Bind(addr_IPvX* _addr,int _addrlen)
{
    if(m_sockId == INVALID_SOCKET)
        throw "Socket is not valid";
    else
    {
        if(bind(m_sockId,_addr,_addrlen) == SOCKET_ERROR)
        {
            throw strerror(errno);
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
    //WSASocket(_family,m_type,_protocol,NULL,0,WSA_FLAG_OVERLAPPED);
    m_sockId = socket(static_cast<int>(m_family),static_cast<int>(m_type), 0);
    if(m_sockId == INVALID_SOCKET)
        throw strerror(errno);
    #ifdef __unix__
    int optval = 1;
	int* tooptval = &optval;
	#endif
	#ifdef _WIN32
    const char* optval = "true";
    #endif
    if(setsockopt(m_sockId, SOL_SOCKET, SO_REUSEADDR, optval, sizeof(optval)))
        throw strerror(errno); 
}
std::vector<NPAddrInfo> Socket::GetAddresses(std::string _ip, int _port, Type _type, Protocol _protocol, Family _family)
{
    addr_info myAddrSpecs;
    addr_info* myAddrInfo;
    std::vector<NPAddrInfo> ret;
    memset(&myAddrSpecs, 0, sizeof(myAddrSpecs));
    myAddrSpecs.ai_family = static_cast<int>(_family);
    myAddrSpecs.ai_socktype = static_cast<int>(_type);
    #if defined(__unix__) || defined(__APPLE__)
    myAddrSpecs.ai_flags = AI_V4MAPPED | AI_ADDRCONFIG;
    #endif
    if(_ip.empty())
        myAddrSpecs.ai_flags |= AI_PASSIVE;
    myAddrSpecs.ai_protocol = static_cast<int>(_protocol);
    const char* port = std::to_string(_port).c_str();
    const char* ip = (_ip.empty())
                        ?   ((char*)nullptr)
                        :   (_ip.c_str());
    int n = getaddrinfo(ip, port , &myAddrSpecs, &myAddrInfo);
#if defined(__unix__) || defined(__APPLE__)
    if(n < 0)
#endif
#ifdef _WIN32
    if(n != 0)
#endif
    {
        throw gai_strerror(n);
    }
    else
    {
        addr_info* next = myAddrInfo;
        ret.clear();
		for (size_t i = 0; next != NULL; ++i, next = next->ai_next)
		{
			ret.emplace_back(NPAddrInfo(next));
		}
    }
    freeaddrinfo(myAddrInfo);
    return ret;
}
bool Socket::IsBound()
{
    return m_isBound;
}
std::string Socket::GetIP(addr_IPvX* _address)
{
    long unsigned int length = (_address->sa_family == AF_INET) ? INET_ADDRSTRLEN : INET6_ADDRSTRLEN;
    std::vector<char> ip(length);
#if defined(__unix__) || defined(__APPLE__)
    inet_ntop(_address->sa_family,_address->sa_data,ip.data(),length);
#endif
#ifdef _WIN32
	if (WSAAddressToString(_address, length, NULL, ip.data(), &length) == SOCKET_ERROR)
	{
		char tmp[256];
		strerror_s(tmp, errno);
		throw tmp;
	}
#endif
    return std::string(ip.data());
}
std::string Socket::GetIP(addr_IPv4* _address)
{
    return GetIP((addr_IPvX*)_address);
}
std::string Socket::GetIP(addr_IPv6* _address)
{
    return GetIP((addr_IPvX*)_address);
}
int Socket::GetPort(addr_IPvX* _address)
{
	return (_address->sa_family == AF_INET)
		? GetPort((addr_IPv4*)_address)
		: GetPort((addr_IPv6*)_address);
}
int Socket::GetPort(addr_IPv4* _address)
{
    return htons(_address->sin_port);
}
int Socket::GetPort(addr_IPv6* _address)
{
    return htons(_address->sin6_port);
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
    WORD wVersionRequested = MAKEWORD(2,2);
    WSADATA wsaData;
	if (WSAStartup(wVersionRequested, &wsaData) != NO_ERROR)
	{
		char tmp[256];
		strerror_s(tmp,errno);
		throw tmp;
	}
    else m_isWsaStarted = true;
}
#endif
