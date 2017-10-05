//
// Created by Clément Péau on 27/09/2017.
//

#include <iostream>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include "AsioServer.hpp"


AsioServer::AsioServer() :
		_shouldRun(true),
		_ioService(),
		_acceptor(_ioService, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), 4242)) {}

AsioServer::~AsioServer()
{
	std::cout << "Destroying AsioServer" << std::endl;
}

bool AsioServer::stop()
{
	//TODO:: STOP SERVER;
	return (true);
}

bool AsioServer::start()
{
	start_accept();
	return (true);
}

void AsioServer::handle_accept(ServerClientObject::shared_ptr new_client, const boost::system::error_code &error)
{
	std::cout << "handle accept\n";
	if (!error)
	{
		new_client->start();
		clientList.push_back(new_client);
		start_accept();
	} else
	{
		std::cerr << error.message() << std::endl;
	}
}

void AsioServer::start_accept()
{
	std::cout << "Im starting to accept\n";
	ServerClientObject::shared_ptr new_client = ServerClientObject::create(_acceptor.get_io_service());

	_acceptor.async_accept(new_client->getSocket(),
	                       boost::bind(&AsioServer::handle_accept, this, new_client, boost::asio::placeholders::error));
}


bool AsioServer::shouldRun()
{
	return (_shouldRun);
}

boost::asio::io_service &AsioServer::getIoService()
{
	return (_ioService);
}

void AsioServer::tick()
{
	_ioService.poll_one();
	_ioService.reset();
}
