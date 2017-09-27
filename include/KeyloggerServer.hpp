//
// Created by Clément Péau on 27/09/2017.
//

#ifndef CPP_SPIDER_KEYLOGGERSERVER_HPP
#define CPP_SPIDER_KEYLOGGERSERVER_HPP

#include "AsioServer.hpp"

class KeyloggerServer : public AsioServer {
public:
	KeyloggerServer();
	~KeyloggerServer();
};

#endif //CPP_SPIDER_KEYLOGGERSERVER_HPP
