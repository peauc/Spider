//
// Created by lavigne on 10/4/17.
//

#ifndef TEST_COMMAND_H
#define TEST_COMMAND_H

# include <string>
# include <map>
# include <cmath>
# include <boost/archive/text_oarchive.hpp>
# include "Module.h"

class   Command
{
public:
    Command();
    ~Command();
    void   process(std::map<char, Module>, std::string, boost::asio::streambuf &);
    t_paquet *getMessageFormat(Module);
};

#endif //TEST_COMMAND_H
