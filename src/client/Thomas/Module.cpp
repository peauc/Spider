//
// Created by lavigne on 10/5/17.
//

#include "Module.h"

Module::Module() {}

Module::~Module() {}

char    Module::getOpcode()
{
    return 0x04;
}

void    Module::addNextData(t_paquet *data)
{
    t_kbData *newData = new t_kbData;

    newData->timestamp = 193;
    newData->key_code = 'A';
    newData->next = data->kbData;
    data->kbData = newData;
}

size_t  Module::getDataSize()
{
    return (sizeof(t_kbData));
}