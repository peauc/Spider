#ifndef IZIHOOK_HH_
#define IZIHOOK_HH_

#include <windows.h>
#include <string>
#include <list>

#ifdef BUILD_DLL
#define DLL_EXPORT __declspec(dllexport)
#else
#define DLL_EXPORT __declspec(dllimport)
#endif


#ifdef __cplusplus
extern "C"
{
#endif


	int __declspec(dllexport) install();

#ifdef __cplusplus
}
#endif

#endif