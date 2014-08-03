#include "socketudp.hpp"
SocketUDP::SocketUDP(std::string _ip, int _port, Family _family, bool _autobind = true)
    : Socket(_ip, _port, Type::Datagram, Protocol::UDP, _family, _autobind)
{

}
SocketUDP::~SocketUDP()
{

}
UDPSenderInfo SocketUDP::Receive()
{
    if(!m_isBound)
        throw "Socket not bound!";
	std::array<char, BUFFER_SIZE> buffer = { '\0' };
    UDPSenderInfo ret;
	socklen_t senderlen = sizeof(ret.sender);
	if (recvfrom(m_sockId, buffer.data(), BUFFER_PACKET_MAX_SIZE, 0, (addr_IPvX*)&ret.sender, &senderlen) == SOCKET_ERROR)
		throw strerror(errno);
	else
		ret.buffer.assign(buffer.data());
    return ret;
}
void SocketUDP::Send(std::string _buffer, addr_storage* _receiver)
{
    if(sendto(m_sockId, _buffer.c_str(), _buffer.length() + 1, 0, (addr_IPvX*)_receiver, sizeof(addr_storage)) == SOCKET_ERROR)
        throw strerror(errno);
}
