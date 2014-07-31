#include "socketudp.hpp"
SocketUDP::SocketUDP(string _ip, int _port, Family _family, bool _autobind)
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
	std::array<char, BUFFER_SIZE> buffer;
	for (char& c : buffer)
		c = '\0';
    UDPSenderInfo ret;
	int n;
	clog << "Awaiting data" << endl;
	socklen_t senderlen = sizeof(ret.sender);
	n = recvfrom(m_sockId, buffer.data(), BUFFER_PACKET_MAX_SIZE, 0, (addr_IPvX*)&ret.sender, &senderlen);
	if (n == SOCKET_ERROR)
	{
#ifdef __unix__
		throw strerror(errno);
#endif
#ifdef _WIN32
		std::cerr << "errore";
#endif
	}
	else
	{
		clog << "Data received" << endl;
		ret.buffer.assign(buffer.data());
	}
    return ret;
}
void SocketUDP::Send(string _buffer, addr_storage* _receiver)
{
    socklen_t recvlen = sizeof(addr_storage);
	ssize_t n = sendto(m_sockId, _buffer.c_str(), _buffer.length() + 1, 0, (addr_IPvX*)_receiver, recvlen);
    if(n == SOCKET_ERROR)
    {
#if defined(__unix__) || defined(__APPLE__)
        throw strerror(errno);
#endif
#ifdef _WIN32
        std::cerr<<"errore";
#endif
    }
}
