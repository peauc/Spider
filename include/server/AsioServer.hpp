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
	boost::asio::ip::tcp::socket tcpSocket;
	boost::asio::io_service _ioService;
};

#endif //CPP_SPIDER_ASIOSERVER_HPP
