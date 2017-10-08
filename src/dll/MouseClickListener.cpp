//
// Created by Quastana Benjamin on 02/10/2017.
//

#include <windows.h>
#include <iostream>
#include <fstream>
#include <time.h>
#include <list>
#include <thread>
#include "../include/Mouse.h"
#include <cstring>

std::list<std::string> list;
bool toerase = false;
HANDLE      mutex;
static bool cont;
static bool cont2;

int getElements(std::list<std::string>& list, std::ofstream& fichier)
{
    std::ifstream temp;
    DWORD result;

    result = WaitForSingleObject(mutex, INFINITE);
    temp.open("../mouse.h");
    if (result == WAIT_OBJECT_0)
    {
        std::string buffer;
        while (std::getline(temp, buffer))
            list.push_back(buffer);
        toerase = true;
        temp.close();
        if (!ReleaseMutex(mutex))
        {
        }
    }
    if (toerase) {
        fichier.close();
        remove("../mouse.txt");
        fichier.open("../mouse.txt");
    }
    return (0);
}

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
    fichier.open("../mouse.txt");

}

MouseClickListener::~MouseClickListener()
{
    fichier.close();
}

void        write_infos(struct s_mouseData mouse, std::ofstream &fichier)
{
    Sleep(30);
    if (fichier)
    {
        fichier << mouse.timestamp << "/" << mouse.x << "/" << mouse.y << "/" << mouse.key_code << std::endl;
        std::cout << mouse.timestamp << "/" << mouse.x << "/" << mouse.y << "/" << mouse.key_code << std::endl;

    }
    else
        printf("File could not be opened\n");
}

void GetMousePos(s_mouseData& mouse, std::ofstream& fichier)
{
    POINT   aPoint;
    time_t rawtime;

    //Check the mouse left button is pressed or not
    if ((GetKeyState(VK_LBUTTON) & 0x100) != 0)
    {
        GetCursorPos(&aPoint);
        mouse.x = aPoint.x;
        mouse.y = aPoint.y;
        time ( &rawtime );
        mouse.timestamp = rawtime;
        mouse.key_code = 1;
        write_infos(mouse, fichier);
    }
        //Check the mouse right button is pressed or not
    else if ((GetKeyState(VK_RBUTTON) & 0x100) != 0)
    {
        GetCursorPos(&aPoint);
        mouse.x = aPoint.x;
        mouse.y = aPoint.y;
        time ( &rawtime );
        mouse.timestamp = rawtime;
        mouse.key_code = 2;
        write_infos(mouse, fichier);
    }
}

int         runThread(s_mouseData& mouse, std::ofstream& fichier)
{
    std::cout << "Run Thread " << std::endl;
    while(cont) {
        GetMousePos(mouse, fichier);
        Sleep(100);
    }
    return (0);
}

int MouseClickListener::run()
{

    CreateThread(0, 0, (LPTHREAD_START_ROUTINE)&runThread, 0, 0, 0);
    return (0);
}

int         MouseClickListener::stop()
{
    cont = false;
    return (0);
}

extern "C" __declspec(dllexport) MouseClickListener *create()
{
    return (new MouseClickListener);
}

extern "C" __declspec(dllexport) void destroy(MouseClickListener *obj)
{
    delete obj;
}

std::string MouseClickListener::getFilenameOutput()
{
    return ("../mouse.txt");
}
