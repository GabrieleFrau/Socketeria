#include "socketudp.hpp"
SocketUDP::SocketUDP(in_port_t _port, Family _family, bool _autobind)
	: Socket(_port, Type::Datagram, Protocol::UDP, _family, _autobind)
{

}
SocketUDP::SocketUDP(std::string _ip, in_port_t _port, Family _family, bool _autobind)
    : Socket(_ip, _port, Type::Datagram, Protocol::UDP, _family, _autobind)
{

}
UDPSenderInfo SocketUDP::Receive()
{
    if(!m_isBound)
        throw "Socket not bound!";
	std::vector<char> buffer(m_bufferSize, '\0');
    UDPSenderInfo ret;
	if (recvfrom(m_sockId, buffer.data(), buffer.size(), 0, reinterpret_cast<addr_IPvX*>(&ret.sender), &ret.senderlen) == SOCKET_ERROR)
		throw strerror(errno);
	else
		ret.buffer.assign(buffer.data());
    return ret;
}
void SocketUDP::Send(std::string _buffer, addr_storage& _receiver)
{
    if(sendto(m_sockId, _buffer.c_str(), _buffer.length(), 0, reinterpret_cast<addr_IPvX*>(&_receiver), sizeof(_receiver)) == SOCKET_ERROR)
        throw strerror(errno);
}
