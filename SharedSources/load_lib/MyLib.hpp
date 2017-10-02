#pragma once

#include <string>

#ifdef MATHFUNCSDLL_EXPORTS
#define MYLIBDLL_API __declspec(dllexport) 
#else
#define MYLIBDLL_API __declspec(dllimport) 
#endif
extern "C"
{
	MYLIBDLL_API int Hello(std::string);
}
//_declspec(dllexport) static MYLIBDLL_API int MyLib2Dll::Hello(std::string);