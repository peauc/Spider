//
// Created by lavigne on 10/4/17.
//

#include <iostream>
#include "client/SpiderClient.hpp"
#include "client/Command.hpp"

Command::Command() {}

Command::~Command() {}

/*
 * Process découpe la commande reçu par le serveur puis la traite.
 */
void                        Command::process(std::map<char, Module> modules, std::string received, boost::asio::streambuf &buf)
{
    std::ostream                    os(&buf);
    boost::archive::text_oarchive   ar(os);
    char                            code = received[0];

    Module                          module = modules[code];
    t_paquet                       *data = getMessageFormat(module);
    ar & data;
}

/*
 * Créer la structure à renvoyer au serveur.
 */
t_paquet                    *Command::getMessageFormat(Module module)
{
    size_t      dataMax = 512 / module.getDataSize();
    t_paquet    *data = new t_paquet;

    data->kbData = NULL;
    data->opcode = 0;
    data->opcode = module.getOpcode();
    for (int i = 0; i < dataMax; i++) {
        module.addNextData(data);
    }
    return data;
}
