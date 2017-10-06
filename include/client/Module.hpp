//
// Created by lavigne on 10/5/17.
//

#ifndef MODULE_HPP
#define MODULE_HPP

# include <glob.h>
# include "SpiderClient.hpp"

class   Module
{
public:
    Module();
    virtual ~Module();
    char    getOpcode();
    void    addNextData(t_paquet *);
    size_t  getDataSize();
};

#endif //MODULE_HPP