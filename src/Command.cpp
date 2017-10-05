//
// Created by lavigne on 10/4/17.
//

#include <iostream>
#include "Command.h"

Command::Command() {}

Command::~Command() {}

/*
 * Process découpe la commande reçu par le serveur puis la traite.
 */
t_paquet           *Command::process(std::map<char, Module> modules, std::string received)
{
  char        code = received[0];
  Module	module;
  t_paquet    *paquet;


  if (modules.find(code) != modules.end())
    return NULL;
  module = modules[code];
  paquet = getMessage(module);
  return paquet;
}

/*
 * Créer la structure à renvoyer au serveur.
 */
t_paquet     *Command::getMessage(Module module)
{
    t_paquet    *paquet = new t_paquet;

        paquet->opcode = module.getOpcode();
        paquet->data = (void *)module.getData();

    return (paquet);
}
