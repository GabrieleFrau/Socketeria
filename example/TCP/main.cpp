#include <iostream>
#include <string>
#include <sockettcp.hpp>
int main(int argc, char* argv[])
{
	try
	{
		SocketTCP socket(8084);
		socket.Listen();
		TCPSenderInfo sender = socket.Accept();
		std::cout << socket.Receive(sender.id) << std::endl;
		socket.Send(sender.id, "Sup?");
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