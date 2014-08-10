#include <iostream>
#include <string>
#include <socketudp.hpp>

int main(int argc, char* argv[])
{
	try
	{
		SocketUDP socket(10009);
		UDPSenderInfo sender = socket.Receive();
		std::cout << sender.buffer << std::endl;
		socket.Send("sup?", sender.sender);
		socket.Close();
	}
	catch (std::exception &e)
	{
		std::cerr << e.what();
	}
	catch (const char* e)
	{
		std::cerr << e;
	}
	catch (int& e)
	{
		std::cerr << e;
	}
	std::cin.get();
	return 0;
}