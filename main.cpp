#include <iostream>
#include "xsocket/socketudp.hpp"
#include "xplatform/platform.hpp"
#include "socketeriaConfig.h"

using namespace std;

int main(int argc, char* argv[])
{
	cout<<argv[0]<<"\tversion "<<SOCKETERIA_VERSION_MAJOR<<"."<<SOCKETERIA_VERSION_MINOR<<endl;
	Platform::ShowCompilerInfo();
	SocketUDP* socket = new SocketUDP("localhost",8080, Family::IPv4);
	cout<<socket->Receive()->buffer<<endl;
	delete socket;
    return 0;
}

