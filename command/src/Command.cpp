//
// Created by lavigne on 10/4/17.
//

#include "Command.h"

Command::Command()
{
    _codeList.push_back(0x01);
    _codeList.push_back(0x02);
    _codeList.push_back(0x03);
    _codeList.push_back(0x04);
    _codeList.push_back(0x05);
    _codeList.push_back(0x06);
}

Command::~Command(){}

/*
 * Process découpe la commande reçu par le serveur puis la traite.
 */
void            Command::process(std::map<char, Spider::Module> modules, std::string received)
{
    char        code = received[0];
    t_paquet    *paquet;

    module = modules[code];
    paquet = getMessage(module, code);
    send(paquet);
}

/*
 * Créer la structure à renvoyer au serveur.
 */
std::string     Command::getMessage(Module module, char code)
{
    t_paquet    *paquet = new t_paquet;

    if (std::find(codeList.begin(), codeList.end(), code) == my_list.end()) {
        paquet->opcode = 0x02;
        paquet->data = NULL;
    } else {
        paquet->opcode = module.getOpcode();
        paquet->data = (void *)module.getData();
    }

    return (paquet);
}

/*
 * Send envoie un message au serveur.
 */
void            Command::send(t_paquet *paquet)
{
    /* trouver comment envoyer avec boost asio la string deja formé) */
    // yourFile.write((char*)&paquet, sizeof paquet);
    std::cout.write((char*)&paquet, sizeof paquet);
}