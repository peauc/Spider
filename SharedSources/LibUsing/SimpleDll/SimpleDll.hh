#ifndef SIMPLEDLL_HH_
#define SIMPLEDLL_HH_

#include <windows.h>
#include <string>
#include <list>

#include "KBData.hpp"

#ifdef BUILD_DLL
#define DLL_EXPORT __declspec(dllexport)
#else
#define DLL_EXPORT __declspec(dllimport)
#endif

struct Object
{
	virtual int Foo(int n) = 0;
	virtual void Release() = 0;
};

#ifdef __cplusplus
extern "C"
{
#endif


#ifdef __cplusplus
}
#endif

#endif