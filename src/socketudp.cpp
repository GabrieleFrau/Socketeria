#include "socketudp.hpp"
SocketUDP::SocketUDP(int _port, Family _family, bool _autobind)
	: Socket(_port, Type::Datagram, Protocol::UDP, _family, _autobind)
{

}
SocketUDP::SocketUDP(std::string _ip, int _port, Family _family, bool _autobind)
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
	if (recvfrom(m_sockId, buffer.data(), BUFFER_PACKET_MAX_SIZE, 0, reinterpret_cast<addr_IPvX*>(&ret.sender), &ret.senderlen) == SOCKET_ERROR)
		throw WSAGetLastError();
	else
		ret.buffer.assign(buffer.data());
    return ret;
}
void SocketUDP::Send(std::string _buffer, addr_storage& _receiver)
{
    if(sendto(m_sockId, _buffer.c_str(), _buffer.length(), 0, reinterpret_cast<addr_IPvX*>(&_receiver), sizeof(_receiver)) == SOCKET_ERROR)
        throw strerror(errno);
}
