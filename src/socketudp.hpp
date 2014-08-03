#ifndef SOCKETUDP_HPP_INCLUDED
#define SOCKETUDP_HPP_INCLUDED
#include "socket.hpp"
class SocketUDP : public Socket
{
public:
    SocketUDP(std::string _ip, int _port, Family _family, bool _autobind);
    ~SocketUDP();

    UDPSenderInfo	Receive();
    void            Send(std::string _buffer, addr_storage* _receiver);
};
#endif // SOCKETUDP_HPP_INCLUDED
