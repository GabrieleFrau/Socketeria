#ifndef SOCKETTCP_HPP_INCLUDED
#define SOCKETTCP_HPP_INCLUDED
#include "socket.hpp"
class SocketTCP : public Socket
{
public:
    SocketTCP(string _ip, int _port, Family _family, bool _autobind = true);
    ~SocketTCP();

    TCPSenderInfo			Accept();
    SOCKET                  Connect(addr_IPvX* _addr, socklen_t _addrlen);
    void                    Listen();
    string                  Receive(SOCKET _sockID);
    void                    Send(SOCKET _sockID, string _buffer);
};
#endif
