//
// Created by Clément Péau on 27/09/2017.
//

#include <iostream>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include "server/AsioServer.hpp"


AsioServer::AsioServer() :
		_shouldRun(true),
		_ioService(),
		_acceptor(_ioService, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), 4242)) {}

AsioServer::~AsioServer()
{
	//TODO: stop
	std::cout << "Destroying AsioServer" << std::endl;
}

bool AsioServer::stop()
{
	_shouldRun = false;
	return (true);
}

bool AsioServer::start()
{
	start_accept();
	return (true);
}

void AsioServer::tick()
{
	_ioService.poll();
	start_accept();
	_clientManager.readOnEveryClient();
	_ioService.reset();
}

void AsioServer::handle_accept(ServerClientObject::shared_ptr newClient, const boost::system::error_code &error)
{
	std::cout << "handle accept\n";
	if (!error)
	{
		_clientManager.addClient(newClient);
		newClient->start();
	} else
	{
		std::cerr << __FUNCTION__ << " " << error.message() << std::endl;
	}
}

void AsioServer::start_accept()
{
	auto newClient = ServerClientObject::create(_ioService);

	_acceptor.async_accept(newClient->getSocket(),
	                       boost::bind(&AsioServer::handle_accept, this, newClient, boost::asio::placeholders::error));
}


bool AsioServer::shouldRun()
{
	return (_shouldRun);
}

boost::asio::io_service &AsioServer::getIoService()
{
	return (_ioService);
}

