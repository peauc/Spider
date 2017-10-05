#ifndef KBHOOK_HH_
#define KBHOOK_HH_

#include <windows.h>
#include <string>
#include <list>

#include "KBData.hpp"

#ifdef BUILD_DLL
#define DLL_EXPORT __declspec(dllexport)
#else
#define DLL_EXPORT __declspec(dllimport)
#endif


class KeyboardListener
{
private:
	std::list<std::thread> threads;
public:

	  static LRESULT CALLBACK CatchLLKeyboardProc
	(const int ncode, const WPARAM wparam, const LPARAM lparam);
	  //static int installHookThread();
	  virtual int installHook(DWORD threadIdn, HINSTANCE inst);
	  virtual int unistallHook();
	  virtual void DoSomething();
	  virtual int getkey();
};

/*#ifdef __cplusplus
extern "C"
{
#endif
	int DLL_EXPORT installHook();
	int DLL_EXPORT unistallHook();



#ifdef __cplusplus
}
#endif*/

#endif