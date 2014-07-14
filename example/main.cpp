#include <iostream>
#include <string>
#include <socketudp.hpp>

int main(int argc, char* argv[])
{
	SocketUDP socket("localhost", 8080, Family::IPv4);
	std::cout << socket.Receive().buffer << std::endl;
	return 0;
}