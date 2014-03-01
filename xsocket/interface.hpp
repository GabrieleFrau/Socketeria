#ifndef SOCKET_INTERFACE_HPP_INCLUDED
#define SOCKET_INTERFACE_HPP_INCLUDED
#include <iostream>
#include "enums.hpp"
#include "types.hpp"
class ISocket
{
public:
    virtual ~ISocket(){};
    virtual void Bind(addr_IPvX* _addr) = 0;
    virtual void Create() = 0;
    virtual void ShutDown() = 0;
};
class IAddress
{
public:
	virtual ~IAddress(){};
	virtual std::string GetIP(addr_IPvX* _address) = 0;
    virtual std::string GetIP(addr_IPv4* _address) = 0;
    virtual std::string GetIP(addr_IPv6* _address) = 0;
    virtual int GetPort(addr_IPvX* _address) = 0;
    virtual int GetPort(addr_IPv4* _address) = 0;
    virtual int GetPort(addr_IPv6* _address) = 0;
};
#endif
