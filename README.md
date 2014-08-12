Socketeria[![Build Status](https://travis-ci.org/GabrieleFrau/Socketeria.svg?branch=master)](https://travis-ci.org/GabrieleFrau/Socketeria) (using gcc 4.8.1 and clang 3.4 on Ubuntu and OSX)
==========

C++ crossplatform socket (tested on windows 8, GNU/linux and MacOSX 10.9)

# Working features
* Basic UDP (single-client <> server) connection (only blocking socket)
* Basic TCP (single-client <> server) connection (only blocking socket)
* IPv4 and IPv6 addresses are both supported (though getaddrinfo() capabilities are still not taken advantage of completely)

# Dependencies
* Any compiler that supports gnu++11/c++11 (Tested on GCC>=4.7, MinGW>=4.7, Clang and MSVC compiler v18)
* CMAKE and MAKE for compiling (>=2.6)
* Doxygen for creating the documentation (>=1.8.6)

# Compiling
```bash
mkdir build
cd build/
cmake..
make
```
## TODO (Check the docs TODO list for more info)
* Parse function for host names and service names
* Comment everything catch(CommentsOverFlowException e){morecomments();}
* Fix horrible error handling
* Moar things
