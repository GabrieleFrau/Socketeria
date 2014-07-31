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
Socket::Socket(string _ip, int _port,Type _type, Protocol _protocol, Family _family, bool _autobind) : Socket(_family,_type,_protocol)
{
    if(_autobind)
    {
        m_addresses = GetAddresses(_ip,_port,_type,_protocol,_family);
		for (size_t i = 0; i < m_addresses.size() && !Bind(&m_addresses[i].ai_addr, m_addresses[i].ai_addrlen); i++);
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
	return this->Bind(_addr, (_addr->sa_family == AF_INET) ? INET_ADDRSTRLEN : INET6_ADDRSTRLEN);
}
bool Socket::Bind(addr_IPvX* _addr,int _addrlen)
{
    if(m_sockId == INVALID_SOCKET)
        throw "Socket is not valid";
    else
    {
#if defined(_WIN32) || defined(__unix__)
        if(bind(m_sockId,_addr,_addrlen) == SOCKET_ERROR)
        {
#ifdef _WIN32
            std::cerr<<"errore";
#endif
#if defined(__unix__) || defined(__APPLE__)
            throw strerror(errno);
#endif
            return m_isBound = false;
        }
        else
            return m_isBound = true;
#endif
		//TODO
#ifdef __APPLE__ 
		bind(m_sockId, _addr, _addrlen);
#endif
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
    m_sockId = socket((int)m_family,(int)m_type, 0);
    if(m_sockId == INVALID_SOCKET)
    {
#ifdef _WIN32
        std::cerr<<"errore";
#endif
#if defined(__unix__) || defined(__APPLE__)
        throw strerror(errno);
#endif
    }
    #ifdef __unix__
    int optval = 1;
    if(setsockopt(m_sockId, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)))
        throw strerror(errno);
    #endif
    #ifdef _WIN32
    const char* optval = "true";
    if(setsockopt(m_sockId, SOL_SOCKET, SO_REUSEADDR, optval, sizeof(optval)))
        std::cerr<<"errore";
    #endif
}
vector<sNPAddrInfo> Socket::GetAddresses(string _ip, int _port, Type _type, Protocol _protocol, Family _family)
{
    addr_info myAddrSpecs;
    addr_info* myAddrInfo;
    vector<sNPAddrInfo> ret;
    memset(&myAddrSpecs, 0, sizeof(myAddrSpecs));
    myAddrSpecs.ai_family = (int)_family;
    myAddrSpecs.ai_socktype = (int)_type;
    #if defined(__unix__) || defined(__APPLE__)
    myAddrSpecs.ai_flags = AI_V4MAPPED | AI_ADDRCONFIG;
    #endif
    if(_ip.empty())
        myAddrSpecs.ai_flags |= AI_PASSIVE;
    myAddrSpecs.ai_protocol = (int)_protocol;
#if defined(__unix__) || defined(__APPLE__)
    const char* port = ::to_string(_port).c_str();
#endif
#ifdef _WIN32
	#ifdef __MINGW32__
		const char* port = Platform::to_string(_port).c_str();
	#elif defined(_MSC_VER)
		char port[20] = { '\0' };
		_itoa_s(_port, port, 10);
	#endif
#endif
    const char* ip = (_ip.empty())
                        ?   ((char*)nullptr)    //if
                        :   (_ip.c_str());      //else
    int n = getaddrinfo(ip, port , &myAddrSpecs, &myAddrInfo);
#if defined(__unix__) || defined(__APPLE__)
    if(n < 0)
#endif
#ifdef _WIN32
    if(n != 0)
#endif
    {
        throw gai_strerror(n);
        #ifdef _WIN32
        std::cerr<<"errore";
        #endif
    }
    else
    {
        addr_info* next = myAddrInfo;
        ret.clear();
		for (size_t i = 0; next != NULL; ++i, next = next->ai_next)
		{
			ret.emplace_back(sNPAddrInfo(next));
		}
    }
    freeaddrinfo(myAddrInfo);
    return ret;
}
bool Socket::IsBound()
{
    return m_isBound;
}
string Socket::GetIP(addr_IPvX* _address)
{
    long unsigned int length = (_address->sa_family == AF_INET) ? INET_ADDRSTRLEN : INET6_ADDRSTRLEN;
    std::vector<char> ip(length);
#if defined(__unix__) || defined(__APPLE__)
    inet_ntop(_address->sa_family,_address->sa_data,ip.data(),length);
#endif
#ifdef _WIN32
	if (WSAAddressToString(_address, length, NULL, ip.data(), &length) == SOCKET_ERROR)
		cerr << "Address to string: ";// << Platform::ShowError(WSAGetLastError()) << ::endl;
#endif
	char tmp[256];
    cerr<<"inet_ntop: "<<strerror_s(tmp,errno)<<::endl;
    exit(errno);
    return string(ip.data());
}
string Socket::GetIP(addr_IPv4* _address)
{
    return GetIP((addr_IPvX*)_address);
}
string Socket::GetIP(addr_IPv6* _address)
{
    return GetIP((addr_IPvX*)_address);
}
int Socket::GetPort(addr_IPvX* _address)
{
    return (_address->sa_family == AF_INET)
            ?GetPort((addr_IPv4*)_address)
            :GetPort((addr_IPv6*)_address);
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
            if(shutdown(m_sockId,2) == -1)
            {
#ifdef _WIN32
                clog<<"shutdown: "<<WSAGetLastError()<<endl;
                if(closesocket(m_sockId) == SOCKET_ERROR)
                    throw WSAGetLastError();
#endif
#if defined(__unix__) || defined(__APPLE__)
                clog<<"shutdown: "<<strerror(errno)<<endl;
                if(close(m_sockId))
                    throw strerror(errno);
#endif
            }
        }
}
#ifdef _WIN32
void Socket::InitWSA()
{
    WORD wVersionRequested = MAKEWORD(2,2);
    WSADATA wsaData;
    int wsastartup = WSAStartup(wVersionRequested, &wsaData);
	if (wsastartup != NO_ERROR)
	{
		char tmp[256];
		throw strerror_s(tmp,errno);
	}
    else m_isWsaStarted = true;
}
#endif
