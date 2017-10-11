//
// Created by thauvi_a on 10/4/17.
//

#include <iostream>
#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <boost/filesystem.hpp>
#include <boost/bind.hpp>
#include "client/AsioClient.hpp"


void AsioClient::handle_read_state(const boost::system::error_code& error)
{
	if (!error)
	{
		std::istream stream_answer(&this->answer);
		unsigned int c_state;
		stream_answer >> c_state;
		std::string m_state;
		std::getline(stream_answer, m_state);
		boost::asio::async_read(this->socket, this->answer,
		                        boost::bind(&AsioClient::handle_read_h, this,
		                                    boost::asio::placeholders::error));
	}
	else
	{
		std::cout << "Error: " << error << "\n";
	}
}

void AsioClient::handle_read_h(const boost::system::error_code& error)
{
	if (!error)
	{
		std::istream stream_answer(&answer);
		std::string header;
		while (std::getline(stream_answer, header) && header != "\n")
			std::cout << header << "\n";
		std::cout << "\n";
		if (answer.size() > 0)
			std::cout << &answer;
		boost::asio::async_read(socket, answer,
		                        boost::asio::transfer_at_least(1),
		                        boost::bind(&AsioClient::handle_read_body, this,
		                                    boost::asio::placeholders::error));
	}
	else
	{
		std::cout << "Error: " << error << "\n";
	}
}

void AsioClient::handle_read_body(const boost::system::error_code& error)
{
	if (!error)
	{
		std::cout << &answer << std::endl;
		boost::asio::async_read(socket, answer,
		                        boost::asio::transfer_at_least(1),
		                        boost::bind(&AsioClient::handle_read_body, this,
		                                    boost::asio::placeholders::error));
	}
	else if (error != boost::asio::error::eof)
	{
		std::cout << "Error: " << error << "\n";
	}
}
