//
// Created by Quastana Benjamin on 02/10/2017.
//

#include <windows.h>
#include <unistd.h>
#include <iostream>
#include <fstream>
#include <time.h>
#include <thread>
#include <stdlib.h>
#include"../include/Mouse.h"

static bool cont2;

int APIENTRY DllMain(HINSTANCE hInstance, DWORD fdwReason, PVOID pvReserved) {
    switch (fdwReason)
    {
        case DLL_PROCESS_ATTACH:
            std::cout << "Processe attached" << std::endl;
            cont2 = true;
            break;
        case DLL_PROCESS_DETACH:
            cont2 = false;
            break;
    }
    return TRUE;
}


MouseClickListener::MouseClickListener() {
    cont = true;
    std::cout << "Hello, World!" << std::endl;
    fichier.open("../test.txt");

}

MouseClickListener::~MouseClickListener()
{
    fichier.close();
}

int         MouseClickListener::runThread()
{
    std::cout << "Run Thread "
         << "cont=" << cont << "cont2=" << cont2 << std::endl;
    while(cont) {
        std::cout << "wesh" << std::endl;
        GetMousePos();
        Sleep(100);
    }
    std::cout << "sortie boucle" << std::endl;
}

int MouseClickListener::run()
{
    //boost::std::thread      t{runThread()};
    std::cout << "run" << std::endl;
    runThread();
     //CreateThread(0, 0, (LPTHREAD_START_ROUTINE)&runThread, 0, 0, 0);
}

int         MouseClickListener::stop()
{
    cont = false;
}

void        write_infos(struct s_mouseData mouse, std::ofstream &fichier)
{
    Sleep(30);
    if (fichier)
    {
        fichier << mouse.timestamp << ":" << mouse.x << ":" << mouse.y << ":" << mouse.key_code << std::endl;
        std::cout << mouse.timestamp << ":" << mouse.x << ":" << mouse.y << ":" << mouse.key_code << std::endl;

    }
    else
        printf("File could not be opened\n");
}

void MouseClickListener::GetMousePos()
{
    POINT   aPoint;
    time_t rawtime;

    //Check the mouse left button is pressed or not
        if ((GetKeyState(VK_LBUTTON) & 0x100) != 0)
        {
            GetCursorPos(&aPoint);
            this->mouse.x = aPoint.x;
            this->mouse.y = aPoint.y;
            time ( &rawtime );
            this->mouse.timestamp = rawtime;
            this->mouse.key_code = 1;
            write_infos(mouse, fichier);
        }
        //Check the mouse right button is pressed or not
        else if ((GetKeyState(VK_RBUTTON) & 0x100) != 0)
        {
            GetCursorPos(&aPoint);
            this->mouse.x = aPoint.x;
            this->mouse.y = aPoint.y;
            time ( &rawtime );
            this->mouse.timestamp = rawtime;
            this->mouse.key_code = 2;
            write_infos(mouse, fichier);
        }
}


extern "C" __declspec(dllexport) MouseClickListener *create()
{
    return (new MouseClickListener);
}

extern "C" __declspec(dllexport) void destroy(MouseClickListener *obj)
{
    delete obj;
}