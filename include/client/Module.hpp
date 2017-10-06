//
// Created by lavigne on 10/5/17.
//

#ifndef TEST_MODULE_HPP
#define TEST_MODULE_HPP

# include <glob.h>
# include "Spider.h"

class   Module
{
public:
    Module();
    virtual ~Module();
    char    getOpcode();
    void    addNextData(t_paquet *);
    size_t  getDataSize();
};

#endif //TEST_MODULE_HPP