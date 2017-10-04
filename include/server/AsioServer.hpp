//
// Created by Clément Péau on 27/09/2017.
//

#ifndef CPP_SPIDER_ASIOSERVER_HPP
#define CPP_SPIDER_ASIOSERVER_HPP

#include "AServer.hpp"
#include "ServerClientObject.hpp"

class AsioServer : public AServer {
public:
	//From base class
	bool stop() override ;
	bool run() override ;

	//From Class
	explicit AsioServer(boost::asio::io_service &ioService);
	AsioServer();
	AsioServer(AsioServer &server) = default;

	virtual ~AsioServer();
	void handle_accept(ServerClientObject::shared_ptr new_client, const boost::system::error_code &error);

private:
	void start_accept();

	boost::asio::io_service _ioService;
	boost::asio::ip::tcp::acceptor _acceptor;

};

#endif //CPP_SPIDER_ASIOSERVER_HPP
