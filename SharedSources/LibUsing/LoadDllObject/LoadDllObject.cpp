// LoadDllObject.cpp : Définit le point d'entrée pour l'application console.
//

#include "stdafx.h"

#include "stdafx.h"
#include <windows.h>
#include <iostream>
#include <thread>

class KeyboardListener
{
public:
	virtual int installHook(DWORD threadIdn, HINSTANCE inst);
	virtual int unistallHook();
	virtual void DoSomething();
	virtual int getkey();
};

//typedef KeyboardListener(__cdecl *f_constr)();
//typedef LRESULT(__cdecl *f_destr)(const int ncode, const WPARAM wparam, const LPARAM lparam);


int main()
{
	HINSTANCE hGetProcIDDLL = LoadLibrary(L"KBHook.dll");

	if (!hGetProcIDDLL)
	{
		std::cout << "Could not laod the dynamic library" << std::endl;
		std::cout << "<Enter> to quit" << std::endl;
		getchar();
		return (42);
	}


	KeyboardListener* (*create)();
	void(*destroy)(KeyboardListener*);

	create = (KeyboardListener* (*)())GetProcAddress(hGetProcIDDLL, "create");
	destroy = (void(*)(KeyboardListener*))GetProcAddress(hGetProcIDDLL, "destroy");

	if (!create && !destroy)
	{
		std::cout << "could not locate the function"
			<< std::endl;
		std::cout << "<Enter> to quit" << std::endl;
		getchar();
		return (43);
	}

	KeyboardListener* obj = (KeyboardListener*)create();
	obj->DoSomething();
	obj->installHook(GetCurrentThreadId(), hGetProcIDDLL);
		Sleep(10000);
	destroy(obj);
	std::cout << "objet detruit" << std::endl;
	getchar();
	return 0;
}

