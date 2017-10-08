//
// Created by lavigne on 10/5/17.
//

#include <string.h>
#include <client/SpiderClient.hpp>
#include "client/Module.hpp"

Module::Module()
{
//    LoadLibrary()
}

Module::~Module()
{

}

char    Module::getOpcode()
{
    if (isKB)
        return 0x04;
    else if (isMouse)
        return 0x05;
    return 0x02;
}

void    Module::getDatas(t_paquet *data) {
    std::list<std::string>  c_datas; // AXEL = ta fonction

    for (std::list<std::string>::iterator it = c_datas.begin(); it != c_datas.end(); it++) {
        std::list<std::string>  c_data;
        std::string             pch;

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
