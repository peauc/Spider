//
// Created by lavigne on 10/4/17.
//

#ifndef TEST_COMMAND_H
#define TEST_COMMAND_H

# include <string>
# include <map>
# include <cmath>
# include "Spider.h"
# include "Module.h"

class   Command
{
public:
    Command();
    ~Command();
    t_paquet    *process(std::map<char, Module>, std::string);
    t_paquet    *getMessage(Module);
};

#endif //TEST_COMMAND_H
