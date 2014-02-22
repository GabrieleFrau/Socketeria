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
#ifdef ISUNIX
            throw strerror(errno);
#endif
#ifdef ISWINZ
            throw Platform::ShowError(WSAGetLastError());
#endif
    return ret;
}
SOCKET SocketTCP::Connect(addr_IPvX* _addr, socklen_t _addrlen)
{
    int so = socket((int)m_family,(int)m_type,0);
    if(so == INVALID_SOCKET)
        throw strerror(errno);
    if(connect(so, _addr , _addrlen))
    {
#ifdef ISUNIX
            throw strerror(errno);
#endif
#ifdef ISWINZ
            throw Platform::ShowError(WSAGetLastError());
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
#ifdef ISWINZ
        throw Platform::ShowError(WSAGetLastError());
#endif
#ifdef ISUNIX
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
#ifdef ISUNIX
        throw strerror(errno);
#endif
#ifdef ISWINZ
        throw Platform::ShowError(WSAGetLastError());
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
#ifdef ISUNIX
    ssize_t n;
#endif
#ifdef ISWINZ
    int n;
#endif
    n = send(_sockID,buffer,bufferlen, 0);
    if(n == SOCKET_ERROR)
    {
#ifdef ISUNIX
        throw strerror(errno);
#endif
#ifdef ISWINZ
        throw Platform::ShowError(WSAGetLastError());
#endif
    }
}
