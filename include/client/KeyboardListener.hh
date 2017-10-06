#ifndef KEYBOARDLISTENER_HH_
#define KEYBOARDLISTENER_HH_

#include <windows.h>
#include <string>
#include <list>

#include "IListener.hh"

typedef int(__cdecl *f_dllfunc)(void);

class KeyboardListener : public IListener
{
private:
	HINSTANCE _dll;

public:
	virtual int run();
	virtual int stop();
	virtual void DoSomething();
};

#endif