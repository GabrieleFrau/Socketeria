#ifndef SOCKETUDP_HPP_INCLUDED
#define SOCKETUDP_HPP_INCLUDED
#include "socket.hpp"
class SocketUDP : public Socket
{
public:
	SocketUDP(in_port_t _port, Family _family = Family::IPv4, bool _autobind = true);
    SocketUDP(std::string _ip, in_port_t _port, Family _family = Family::IPv4, bool _autobind = true);
    ~SocketUDP() = default;

    UDPSenderInfo	Receive();
    void            Send(std::string _buffer, addr_storage& _receiver);
};
#endif // SOCKETUDP_HPP_INCLUDED
