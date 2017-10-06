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
	boost::asio::async_write(_socket, boost::asio::buffer("hello client\n"),
	                         boost::bind(&ServerClientObject::handle_write, shared_from_this(),
	                                     boost::asio::placeholders::error,
	                                     boost::asio::placeholders::bytes_transferred));
}

void ServerClientObject::handle_write(const boost::system::error_code &error /*error*/, size_t bytes/*bytes_transferred*/)
{
	std::cout << "Has writen " << bytes << std::endl;
}

void ServerClientObject::tryReading()
{
	boost::asio::async_read(_socket, _buffer,
	                        boost::asio::transfer_at_least(1),
	                        boost::bind(&ServerClientObject::readContentHandler, this,
	                                    boost::asio::placeholders::error));
}

void ServerClientObject::readContentHandler(const boost::system::error_code &err)
{
	if (!err)
	{
		// Write all of the data that has been read so far.
		std::cout << &_buffer;

		// Continue reading remaining data until EOF.
		boost::asio::async_read(_socket, _buffer,
		                        boost::asio::transfer_at_least(1),
		                        boost::bind(&ServerClientObject::readContentHandler, this,
		                                    boost::asio::placeholders::error));
	} else if (err != boost::asio::error::eof)
	{
		std::cout << "Error: " << err << "\n";
	}
}
