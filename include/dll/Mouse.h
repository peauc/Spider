//
// Created by Quastana Benjamin on 05/10/2017.
//

#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCUnusedGlobalDeclarationInspection"
#ifndef TESTMOUSE_MOUSE_H_H
#define TESTMOUSE_MOUSE_H_H

#include "IListener.hh"

struct         s_mouseData
{
    int            timestamp;
    int            key_code;
    int            x;
    int            y;
    struct    s_mouseData    *next;
};

class MouseClickListener : public IListener
{
public:
    MouseClickListener();
    ~MouseClickListener();
    virtual int run();
    virtual int stop();
	virtual std::string getFilenameOutput();

private:
    s_mouseData     mouse;
    std::ofstream   fichier;
};

#endif //TESTMOUSE_MOUSE_H_H

#pragma clang diagnostic pop