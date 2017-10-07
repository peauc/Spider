//
// Created by Axel Drozdzynski on 07/10/2017.
//

#include <windows.h>
#include <string>
#include <iostream>

#include "IListener.hh"

int main()
{
    std::cout << "Hello World" << std::endl;
    HINSTANCE hGetProcIDDLL = LoadLibrary("libKeyboardListener.dll");

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