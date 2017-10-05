//
// Created by lavigne on 10/5/17.
//

# include "Module.h"

Module::Module() {}

Module::~Module() {}

char    Module::getOPcode()
{
    return _opcode;
}

void    *Module::getData()
{
    t_mouseData *data;

    data->timestamp = 193;
    data->key_code = 'A';
    return (void *)data;
}