//
// Created by lavigne on 10/5/17.
//

#ifndef TEST_MODULE_H
#define TEST_MODULE_H

# include "Spider.h"

class   Module
{
public:
    Module();
    virtual ~Module();
    char getOpcode();
    void    *getData();
};

#endif //TEST_MODULE_H
