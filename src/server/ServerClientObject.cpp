//
// Created by Clément Péau on 04/10/2017.
//

#include <iostream>
#include <boost/bind.hpp>
#include "ServerClientObject.hpp"

ServerClientObject::shared_ptr ServerClientObject::create(boost::asio::io_service &io_service)
{
	std::cout << "creating a new ServerClientObject\n";
	return shared_ptr(new ServerClientObject(io_service));
}

boost::asio::ip::tcp::socket &ServerClientObject::getSocket()
{
	return (_socket);
}

void ServerClientObject::start()
{
	std::cout << "Starting a new client\n";
	// The data to be sent is stored in the class member m_message
	// as we need to keep the data valid
	// until the asynchronous operation is complete.

	// When initiating the asynchronous operation,
	// and if using boost::bind(),
	// we must specify only the arguments
	// that match the handler's parameter list.
	// In this code, both of the argument placeholders
	// (boost::asio::placeholders::error
	// and boost::asio::placeholders::bytes_transferred)
	// could potentially have been removed,
	// since they are not being used in handle_write().
	boost::asio::async_write(_socket, boost::asio::buffer("hello client\n"),
	                         boost::bind(&ServerClientObject::handle_write, shared_from_this(),
	                                     boost::asio::placeholders::error,
	                                     boost::asio::placeholders::bytes_transferred));
}

void ServerClientObject::handle_write(const boost::system::error_code &error /*error*/, size_t bytes/*bytes_transferred*/)
{
	std::cout << "Has writen " << bytes << std::endl;
}

