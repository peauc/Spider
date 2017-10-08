//
// Created by Axel Drozdzynski on 07/10/2017.
//

#include <windows.h>
#include <string>
#include <iostream>
#include <list>

#include "IListener.hh"

void displayList(std::list<std::string>& l)
{
	std::list<std::string>::iterator it;

	it = l.begin();
	std::cout << "List.size = " << l.size() << std::endl;
	while (it != l.end())
	{
		std::cout << *it << std::endl;
		++it;
	}
}

int main()
{
    std::cout << "Hello World" << std::endl;
    HINSTANCE hGetProcIDDLL = LoadLibrary("MouseClickListener.dll");
	std::list<std::string> list;

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
	obj->getElements(list);
    obj->stop();
    destroy(obj);
    std::cout << "objet detruit" << std::endl;
    getchar();
    FreeLibrary(hGetProcIDDLL);
	std::cout << "List content :" << std::endl;
	displayList(list);
	getchar();
	getchar();
	Sleep(3000);
    return 0;
}