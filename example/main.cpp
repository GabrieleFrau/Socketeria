#include <iostream>
#include <string>
#include <sockettcp.hpp>
#include <socketudp.hpp>

int main(int argc, char* argv[])
{
	/*
	try
	{
		SocketTCP socket(8084);
		socket.Listen();
		TCPSenderInfo sender = socket.Accept();
		std::cout << socket.Receive(sender.id) << std::endl;
		socket.Send(sender.id, "Sup?");
		socket.Close();
	}
	/**/
	try
	{
		SocketUDP socket2(10009);
		UDPSenderInfo sender = socket2.Receive();
		std::cout << sender.buffer << std::endl;
		socket2.Send("sup?", sender.sender);
		socket2.Close();
	}
	/**/
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
	/**/
	std::cin.get();
	return 0;
}