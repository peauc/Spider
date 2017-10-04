//
// Created by Clément Péau on 27/09/2017.
//

#include <iostream>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include "AsioServer.hpp"

AsioServer::~AsioServer()
{
}

AsioServer::AsioServer(boost::asio::io_service &io_service) : _acceptor(io_service, boost::asio::ip::tcp::endpoint(
		boost::asio::ip::tcp::v4(), 4242))
{
// start_accept() creates a get_socket and
// initiates an asynchronous accept operation
// to wait for a new connection.
	std::cout << "start accept\n";
	start_accept();
}



// handle_accept() is called when the asynchronous accept operation
// initiated by start_accept() finishes. It services the ServerClientObject request
void AsioServer::handle_accept(ServerClientObject::shared_ptr new_client, const boost::system::error_code &error)
{
	std::cout << "handle accept\n";
	if (!error)
	{
		new_client->start();
	}
	else {
		std::cerr << error.message() << std::endl;
	}

	// Call start_accept() to initiate the next accept operation.
	start_accept();
}

bool AsioServer::stop()
{
	//TODO:: STOP SERVER;
	return (true);
}

bool AsioServer::run()
{
	start_accept();
	return (true);
}

void AsioServer::start_accept()
{
	// creates a get_socket
	std::cout << "Im starting to accept\n";
	ServerClientObject::shared_ptr new_client = ServerClientObject::create(_acceptor.get_io_service());

	// initiates an asynchronous accept operation
	// to wait for a new connection.
	_acceptor.async_accept(new_client->getSocket(),
	                       boost::bind(&AsioServer::handle_accept, this, new_client, boost::asio::placeholders::error));
}

AsioServer::AsioServer() : _ioService(), _acceptor(_ioService, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), 4242)) {}
