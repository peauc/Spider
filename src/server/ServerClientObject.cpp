//
// Created by Clément Péau on 04/10/2017.
//

#include <iostream>
#include <boost/bind.hpp>
#include "server/ServerClientObject.hpp"

ServerClientObject::shared_ptr ServerClientObject::create(boost::asio::io_service &io_service)
{
	return shared_ptr(new ServerClientObject(io_service));
}

boost::asio::ip::tcp::socket &ServerClientObject::getSocket()
{
	return (_socket);
}

void ServerClientObject::write(const std::string &message)
{
	boost::asio::async_write(_socket, boost::asio::buffer(message),
	                         boost::bind(&ServerClientObject::handle_write, shared_from_this(),
	                                     boost::asio::placeholders::error,
	                                     boost::asio::placeholders::bytes_transferred));
}

void ServerClientObject::start()
{
	std::cout << "Starting a new client\n";
	write("HelloClient\n");
}

void ServerClientObject::handle_write(const boost::system::error_code &error, size_t bytes)
{
	if (error)
	{
		std::cerr << error << std::endl;
	}
	else
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
		_inputBuffer << &_buffer;

		boost::asio::async_read(_socket, _buffer,
		                        boost::asio::transfer_at_least(1),
		                        boost::bind(&ServerClientObject::readContentHandler, this,
		                                    boost::asio::placeholders::error));
	} else if (err != boost::asio::error::eof)
	{
		//std::cout << __FUNCTION__ <<" error: " << err << "\n";
	}
}
std::string ServerClientObject::getInputBuffer()
{
	std::string string;

	string = _inputBuffer.str();
	return (string);
}

void ServerClientObject::resetInputBuffer()
{
	_inputBuffer.clear();
	_inputBuffer.str("");
}


