#include "socketudp.hpp"
SocketUDP::SocketUDP(string _ip, int _port, Family _family, bool _autobind)
    : Socket(_ip, _port, Type::Datagram, Protocol::UDP, _family, _autobind)
{

}
SocketUDP::~SocketUDP()
{

}
UDPsenderInfo* SocketUDP::Receive()
{
    if(!m_isBound)
        throw "Socket not bound!";
    char buffer[BUFFER_SIZE];
    memset(buffer,'\0',BUFFER_SIZE);
    UDPsenderInfo* ret = new sUDPSenderInfo();
    if(ret != NULL)
        ret->sender = new sockaddr_storage();
    int n;
    clog<<"Awaiting data"<<endl;
    socklen_t senderlen = (ret->sender->ss_family == AF_INET)?sizeof(addr_IPv4):sizeof(addr_IPv6);
    n = recvfrom(m_sockId,buffer,BUFFER_PACKET_MAX_SIZE,0,(addr_IPvX*)ret->sender,&senderlen);
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
        ret->buffer.assign(buffer);
    }
    return ret;
}
void SocketUDP::Send(string _buffer, addr_storage* _receiver)
{
    const char* buffer = _buffer.c_str();
    size_t bufferlen = _buffer.length() + 1;
    socklen_t recvlen = sizeof(addr_storage);
#if defined(__unix__) || defined(__APPLE__)
    ssize_t n;
#endif
#ifdef ISWINZ
    int n;
#endif
    n = sendto(m_sockId, buffer,bufferlen,0,(addr_IPvX*)_receiver,recvlen);
    if(n == SOCKET_ERROR)
    {
#if defined(__unix__) || defined(__APPLE__)
        throw strerror(errno);
#endif
#ifdef ISWINZ
        throw Platform::ShowError(WSAGetLastError());
#endif
    }
}
