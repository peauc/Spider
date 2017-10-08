//
// Created by Clément Péau on 27/09/2017.
//

#ifndef CPP_SPIDER_ASIOSERVER_HPP
#define CPP_SPIDER_ASIOSERVER_HPP

#define NUMBER_OF_POLL_PER_TICK 3

#include "ClientObjectManager.hpp"
#include "server/AServer.hpp"
#include "server/ServerClientObject.hpp"

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
	void sendToEveryClient(const std::string &string);
	void handle_accept(ServerClientObject::shared_ptr newClient, const boost::system::error_code &error);
	virtual void tick();



private:
	void start_accept();

	ClientObjectManager     _clientManager;
	bool                    _shouldRun;
	boost::asio::io_service _ioService;
	boost::asio::ip::tcp::acceptor _acceptor;

};

#endif //CPP_SPIDER_ASIOSERVER_HPP
