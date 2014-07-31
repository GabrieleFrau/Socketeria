#ifndef INTERFACE_HPP_INCLUDED
#define INTERFACE_HPP_INCLUDED
#include <iostream>
#include "enums.hpp"
#include "types.hpp"
class ISocket
{
public:
    virtual ~ISocket() = default;
    virtual bool Bind(addr_IPvX* _addr) = 0;
    virtual void Create() = 0;
    virtual void ShutDown() = 0;
};
class IAddress
{
public:
	virtual ~IAddress() = default;
	virtual std::string GetIP(addr_IPvX* _address) = 0;
    virtual std::string GetIP(addr_IPv4* _address) = 0;
    virtual std::string GetIP(addr_IPv6* _address) = 0;
    virtual int GetPort(addr_IPvX* _address) = 0;
    virtual int GetPort(addr_IPv4* _address) = 0;
    virtual int GetPort(addr_IPv6* _address) = 0;
};
#endif
