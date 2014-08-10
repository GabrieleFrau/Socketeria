#include "sockettcp.hpp"
SocketTCP::SocketTCP(int _port, Family _family, bool _autobind)
	: Socket(_port, Type::Stream, Protocol::TCP, _family, _autobind)
{

}
SocketTCP::SocketTCP(std::string _ip, int _port, Family _family, bool _autobind)
    : Socket(_ip, _port, Type::Stream, Protocol::TCP, _family , _autobind)
{
}
SocketTCP::~SocketTCP()
{

}
TCPSenderInfo SocketTCP::Accept()
{
    TCPSenderInfo ret;
	ret.id = accept(m_sockId, reinterpret_cast<addr_IPvX*>(&ret.sender), &ret.senderlen);
	if (ret.id == SOCKET_ERROR)
		throw strerror(errno);
    return ret;
}
SOCKET SocketTCP::Connect(addr_IPvX& _addr, socklen_t _addrlen)
{
	SOCKET so = socket(static_cast<int>(m_family), static_cast<int>(m_type), 0);
	if (so == INVALID_SOCKET)
		throw strerror(errno);
    if(connect(so, &_addr , _addrlen))
        throw strerror(errno);
    return so;
}
void SocketTCP::Listen()
{
    if(m_sockId == INVALID_SOCKET)
        throw "Invalid socket";
    if(!m_isBound)
        throw "Socket not bound";
	if (listen(m_sockId, 2) == SOCKET_ERROR)
        throw strerror(errno);
}
std::string SocketTCP::Receive(SOCKET _sockID)
{
    if(!m_isBound)
        throw "Socket not bound!";
	std::vector<char> buffer(m_bufferSize, '\0');
    if(recv(_sockID, buffer.data(), buffer.size(), 0) == SOCKET_ERROR)
        throw strerror(errno);
    return buffer.data();
}
void SocketTCP::Send(SOCKET _sockID, std::string _buffer)
{
    if(send(_sockID, _buffer.c_str(),_buffer.length(), 0) == SOCKET_ERROR)
        throw strerror(errno);
}
