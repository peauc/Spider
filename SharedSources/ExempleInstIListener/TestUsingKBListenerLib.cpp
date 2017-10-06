// TestUsingKBListenerLib.cpp : Définit le point d'entrée pour l'application console.
//

#include "stdafx.h"

#include <windows.h>
#include <string>
#include <iostream>

#include "IListener.hh"

int main()
{
	HINSTANCE hGetProcIDDLL = LoadLibrary(L"KeyboardListener.dll");

	if (!hGetProcIDDLL)
	{
		std::cout << "Could not laod the dynamic library" << std::endl;
		std::cout << "<Enter> to quit" << std::endl;
		getchar();
		return (42);
	}


	IListener* (*create)();
	void(*destroy)(IListener*);

	create = (IListener* (*)())GetProcAddress(hGetProcIDDLL, "create");
	destroy = (void(*)(IListener*))GetProcAddress(hGetProcIDDLL, "destroy");

	if (!create && !destroy)
	{
		std::cout << "could not locate the function"
			<< std::endl;
		std::cout << "<Enter> to quit" << std::endl;
		getchar();
		return (43);
	}

	IListener* obj = (IListener*)create();
	obj->run();
	getchar();
	obj->stop();
	destroy(obj);
	std::cout << "objet detruit" << std::endl;
	getchar();
	return 0;
}


