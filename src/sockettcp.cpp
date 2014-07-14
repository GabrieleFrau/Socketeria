#include "sockettcp.hpp"
SocketTCP::SocketTCP(string _ip, int _port, Family _family, bool _autobind)
    : Socket(_ip, _port, Type::Stream, Protocol::TCP, _family , _autobind)
{
}
SocketTCP::~SocketTCP()
{

}
TCPsenderInfo* SocketTCP::Accept()
{
    TCPsenderInfo* ret = new sTCPSenderInfo;
    ret->senderlen = (socklen_t)sizeof(addr_storage);
    ret->id = accept(m_sockId,(addr_IPvX*)ret->sender,&ret->senderlen);
    if(ret->id == SOCKET_ERROR)
#if defined(__unix__) || defined(__APPLE__)
            throw strerror(errno);
#endif
#ifdef _WIN32
            std::cerr<<"errore";
#endif
    return ret;
}
SOCKET SocketTCP::Connect(addr_IPvX* _addr, socklen_t _addrlen)
{
    SOCKET so = socket((int)m_family,(int)m_type,0);
	if (so == INVALID_SOCKET)
	{
		char tmp[256];
		throw strerror_s(tmp,errno);
	}
    if(connect(so, _addr , _addrlen))
    {
#ifdef ISUNIX
            throw strerror(errno);
#endif
#ifdef _WIN32
            std::cerr<<"errore";
#endif
    }
    return so;
}
void SocketTCP::Listen()
{
    if(m_sockId == INVALID_SOCKET)
        throw "Invalid socket";
    if(!m_isBound)
        throw "Socket not bound";
    if(listen(m_sockId,2) == SOCKET_ERROR)
#ifdef _WIN32
        std::cerr<<"errore";
#endif
#if defined(__unix__) || defined(__APPLE__)
        throw strerror(errno);
#endif
}
string SocketTCP::Receive(SOCKET _sockID)
{
    if(!m_isBound)
        throw "Socket not bound!";
    char buffer[BUFFER_SIZE];
    memset(buffer,'\0',BUFFER_SIZE);
    int n;
    n = recv(_sockID, buffer, BUFFER_PACKET_MAX_SIZE, 0);
    if(n == SOCKET_ERROR)
    {
#if defined(__unix__) || defined(__APPLE__)
        throw strerror(errno);
#endif
#ifdef _WIN32
        std::cerr<<"errore";
#endif
    }
    else
    {
        clog<<"Data received"<<endl;
    }
    return buffer;
}
void SocketTCP::Send(SOCKET _sockID, string _buffer)
{
    const char* buffer = _buffer.c_str();
    size_t bufferlen = _buffer.length();
#if defined(__unix__) || defined(__APPLE__)
    ssize_t n;
#endif
#ifdef _WIN32
    int n;
#endif
    n = send(_sockID,buffer,bufferlen, 0);
    if(n == SOCKET_ERROR)
    {
#if defined(__unix__) || defined(__APPLE__)
        throw strerror(errno);
#endif
#ifdef _WIN32
        std::cerr<<"errore";
#endif
    }
}
