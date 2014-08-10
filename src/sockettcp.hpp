#ifndef SOCKETTCP_HPP_INCLUDED
#define SOCKETTCP_HPP_INCLUDED
#include "socket.hpp"
class SocketTCP : public Socket
{
public:
	SocketTCP(int _port, Family _family = Family::IPv4, bool _autobind = true);
    SocketTCP(std::string _ip, int _port, Family _family = Family::IPv4, bool _autobind = true);
    ~SocketTCP();

    TCPSenderInfo			Accept();
    SOCKET                  Connect(addr_IPvX& _addr, socklen_t _addrlen);
    void                    Listen();
    std::string             Receive(SOCKET _sockID);
    void                    Send(SOCKET _sockID, std::string _buffer);
};
#endif
