#include <iostream>
#include <string>
#include <sockettcp.hpp>
#include <socketudp.hpp>

int main(int argc, char* argv[])
{
	SocketTCP socket("localhost", 8080, Family::IPv4);
	socket.Listen();
	SOCKET sender = socket.Accept().id;
	std::cout << socket.Receive(sender) << std::endl;
	socket.Close();
	SocketUDP socket2("localhost", 8081, Family::IPv4);
	std::cout << socket2.Receive().buffer << std::endl;
	socket2.Close();
	std::cin.get();
	return 0;
}