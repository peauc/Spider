//
// Created by lavigne on 10/4/17.
//

#ifndef TEST_COMMAND_H
#define TEST_COMMAND_H

# include <string>
# include <map>
# include <cmath>
# include "Spider.h"

class   Command
{
public:
    Command();
    ~Command();
    void        process(std::map<char, Spider::Module>, std::string);
    t_paquet    getMessage(Spider::Module, char);
    void        send(t_paquet);
private:
    std::list<char>  _codeList;
};

#endif //TEST_COMMAND_H
