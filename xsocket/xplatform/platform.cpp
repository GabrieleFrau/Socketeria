#include "platform.hpp"


void Platform::ShowCompilerInfo()
{
#ifdef __GNUC__
    const char* version = __VERSION__;
#endif
#ifdef _MSC_VER
	const int version = _MSC_VER;
#endif
    const char* data = __DATE__;
    const char* time = __TIME__;
    const int standard = __cplusplus;
    std::cout<<std::endl<<"Compiler information:"<<std::endl
                        <<"\tCompiler version: "<<version<<std::endl
                        <<"\tDate: "<<data<<" "<<time<<std::endl
                        <<"\tC++ Standard: "<<standard<<std::endl
						<<std::endl;
}
#ifdef ISWINZ
std::string Platform::to_string(int value)
{
    std::stringstream ss;
    ss << value;
    return ss.str();
}
std::string Platform::ShowError(HRESULT hresult)
{
    LPTSTR errorText = NULL;
                FormatMessage(
                // use system message tables to retrieve error text
                FORMAT_MESSAGE_FROM_SYSTEM
                // allocate buffer on local heap for error text
                |FORMAT_MESSAGE_ALLOCATE_BUFFER
                // Important! will fail otherwise, since we're not
                // (and CANNOT) pass insertion parameters
                |FORMAT_MESSAGE_IGNORE_INSERTS,
                NULL,    // unused with FORMAT_MESSAGE_FROM_SYSTEM
                hresult,
                MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
                (LPTSTR)&errorText,  // output
                0, // minimum size for output buffer
                NULL);   // arguments - see note
                return std::string(errorText);
}
#endif
