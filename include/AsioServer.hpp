//
// Created by Clément Péau on 27/09/2017.
//

#ifndef CPP_SPIDER_ASIOSERVER_HPP
#define CPP_SPIDER_ASIOSERVER_HPP

#include <boost/asio.hpp>
#include "AServer.hpp"

class AsioServer : public AServer {
public:
	AsioServer();
	virtual ~AsioServer();
private:
	boost::asio::io_service _io_service;
};

#endif //CPP_SPIDER_ASIOSERVER_HPP
