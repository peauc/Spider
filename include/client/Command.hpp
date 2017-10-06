//
// Created by lavigne on 10/4/17.
//

#ifndef COMMAND_HPP
#define COMMAND_HPP

# include <string>
# include <map>
# include <cmath>
# include <boost/archive/text_oarchive.hpp>
# include "client/Module.hpp"

class Module;
typedef struct s_paquet t_paquet;

class   Command
{
public:
    Command();
    ~Command();
    void   process(std::map<char, Module>, std::string, boost::asio::streambuf &);
    t_paquet *getMessageFormat(Module);
};

#endif //COMMAND_HPP
