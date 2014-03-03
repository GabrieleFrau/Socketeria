#ifndef PLATFORM_HPP_INCLUDED
#define PLATFORM_HPP_INCLUDED
#include <iostream>
#ifdef __unix__
#include <sys/utsname.h>
#include <cstring>
typedef struct utsname UnixInfo;
#endif
#ifdef _WIN32
#include <string>
#include <sstream>
#include <windows.h> ///< \bug You have to manually edit #include from <winsock.h> to <winsock2.h>
#endif
class Platform
{
public:
    static void ShowCompilerInfo();
#ifdef _WIN32
    static std::string ShowError(HRESULT hresult);
    static std::string to_string(int value);
#endif
};
#endif
