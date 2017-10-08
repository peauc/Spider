//
// Created by Quastana Benjamin on 02/10/2017.
//

#include <windows.h>
#include <iostream>
#include <time.h>
#include <list>
#include <thread>
#include <string>
#include <mutex>

#include "Mouse.h"

std::list<std::string> list;
bool toerase = false;
//HANDLE      mutex;
static bool cont;
static bool cont2;
std::mutex mutex;
std::ofstream   fichier;

int getElementsA(std::list<std::string>& list, std::ofstream& fichier)
{
    std::ifstream temp;
   // DWORD result;

    temp.open("mouse.txt");
	mutex.lock();
		std::string buffer;
		while (getline(temp, buffer))
			list.push_back(buffer);
		toerase = true;
		temp.close();
		fichier.close();
		remove("mouse.txt");
		fichier.open("mouse.txt");
		mutex.unlock();
	return (0);
}

int MouseClickListener::getElements(std::list<std::string>& list)
{
	return (getElementsA(list, fichier));
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
}

MouseClickListener::~MouseClickListener()
{
    fichier.close();
}

void        write_infos(struct s_mouseData mouse)
{
    Sleep(30);
    if (fichier.is_open())
    {
		
        fichier << mouse.timestamp << "/" << mouse.x << "/" << mouse.y << "/" << mouse.key_code << std::endl;
        std::cout << mouse.timestamp << "/" << mouse.x << "/" << mouse.y << "/" << mouse.key_code << std::endl;
    }
    else
        printf("File could not be opened\n");
}

void GetMousePos()
{
    POINT   aPoint;
    time_t rawtime;
	s_mouseData     mouse;
	SHORT r;

	std::cout << "UP" << std::endl;
    //Check the mouse left button is pressed or not
    if ((r = GetKeyState(VK_LBUTTON) & 0x80) != 0)
    {
		std::cout << "CLICK" << std::endl;
        GetCursorPos(&aPoint);
        mouse.x = aPoint.x;
        mouse.y = aPoint.y;
        time ( &rawtime );
        mouse.timestamp = rawtime;
        mouse.key_code = 1;
        write_infos(mouse);

    }
        //Check the mouse right button is pressed or not
    else if ((r = GetKeyState(VK_RBUTTON) & 0x80) != 0)
    {
        GetCursorPos(&aPoint);
        mouse.x = aPoint.x;
        mouse.y = aPoint.y;
        time ( &rawtime );
        mouse.timestamp = rawtime;
        mouse.key_code = 2;
        write_infos(mouse);
		std::cout << "CLICK" << std::endl;
	}
	std::cout << "r = " << (r & 0x80) << std::endl;
}

std::string GetLastErrorStdStr()
{
	DWORD error = GetLastError();
	if (error)
	{
		LPVOID lpMsgBuf;
		DWORD bufLen = FormatMessage(
			FORMAT_MESSAGE_ALLOCATE_BUFFER |
			FORMAT_MESSAGE_FROM_SYSTEM |
			FORMAT_MESSAGE_IGNORE_INSERTS,
			NULL,
			error,
			MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
			(LPTSTR)&lpMsgBuf,
			0, NULL);
		if (bufLen)
		{
			LPCSTR lpMsgStr = (LPCSTR)lpMsgBuf;
			std::string result(lpMsgStr, lpMsgStr + bufLen);

			LocalFree(lpMsgBuf);

			return result;
		}
	}
	return std::string();
}

int         runThread()
{
	fichier.open("mouse.txt");
    std::cout << "Run Thread " << std::endl;

    while(cont) 
	{
		//std::cout << "INFINITE " << std::endl;
		mutex.lock();
		std::cout << "result" << std::endl;
		GetMousePos();
		mutex.unlock();
		Sleep(100);
    }
	fichier.close();
    return (0);
}

int MouseClickListener::run()
{
    CreateThread(0, 0, (LPTHREAD_START_ROUTINE)&runThread, 0, 0, 0);
	//runThread();
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
    return ("mouse.txt");
}
