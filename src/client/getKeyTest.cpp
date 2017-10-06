//
// Created by lavigne on 9/28/17.
//

#include <windows.h>
#include <fstream>
using namespace std;

int main()
{
    int counter=0;
    ofstream myfile;
    myfile.open("example.txt");
    while(true)
    {
        if(GetAsyncKeyState(VK_ESCAPE))
        {
            counter++;
            myfile <<"Escape : " <<counter;
        }
        Sleep(10); // NEW LINE OF CODE - pauses for 10 milliseconds
    }
    return 0;
}