#ifndef INTERFACE_HPP_INCLUDED
#define INTERFACE_HPP_INCLUDED
#include <iostream>
#include "enums.hpp"
#include "types.hpp"
class ISocket
{
public:
    virtual ~ISocket() = default;
    virtual bool Bind(addr_IPvX& _addr) = 0;
    virtual void Create() = 0;
    virtual void ShutDown() = 0;
};
#endif
