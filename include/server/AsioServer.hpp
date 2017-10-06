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
	bool start() override ;

	AsioServer();
	AsioServer(AsioServer &server) = delete;
	~AsioServer() override ;

	boost::asio::io_service &getIoService();
	bool shouldRun();
	void handle_accept(ServerClientObject::shared_ptr new_client, const boost::system::error_code &error);
	void tick();
	bool sendMessageToClient(ServerClientObject &client, std::string message);
	bool sendMessageToEveryClient(std::string message);

private:
	void start_accept();
	std::vector<ServerClientObject::shared_ptr> clientList;
	bool                    _shouldRun;
	boost::asio::io_service _ioService;
	boost::asio::ip::tcp::acceptor _acceptor;

};

#endif //CPP_SPIDER_ASIOSERVER_HPP
