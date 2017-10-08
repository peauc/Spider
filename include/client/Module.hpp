//
// Created by lavigne on 10/5/17.
//

#ifndef MODULE_HPP
#define MODULE_HPP

# include "client/SpiderClient.hpp"

class   Module
{
    std::string _filenameListener;
public:
    Module(std::string filenameListener);
    Module();
    //Module(Module &copy);
    void    setFilenameListener(std::string filenameListener);
    void    run();

    virtual ~Module();
    char    getOpcode(); // identifier module
    void    getDatas(t_paquet *);
    std::string getFilename();

    Module& operator=(Module copy);
};



#endif //MODULE_HPP