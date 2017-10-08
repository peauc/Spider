//
// Created by Quastana Benjamin on 05/10/2017.
//

#ifndef MOUSE_H_
#define MOUSE_H_

#include <fstream>

#include "IListener.hh"

struct         s_mouseData
{
    time_t            timestamp;
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
	virtual int	getElements(std::list<std::string>& list);

private:
    s_mouseData     mouse;
};

#endif //TESTMOUSE_MOUSE_H_H