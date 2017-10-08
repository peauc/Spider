//
// Created by Clément Péau on 27/09/2017.
//

#include "server/Utils.hpp"
#include "server/SpiderServer.hpp"
#include <iostream>

SpiderServer::SpiderServer() :
		_stdIn(getIoService()),
		_opCodeDuet (std::vector<std::pair<char, std::string>> { {0x04, "SendKb"}, {0x05, "SendMo"}, {0x06, "SendSs"} })
{
	_stdIn.assign(STDIN_FILENO);
	std::cout << "SpiderServer is launching" << std::endl;
}

SpiderServer::~SpiderServer()
{

}

void SpiderServer::queueReadingFromTerminal()
{
	boost::asio::async_read(_stdIn, _buffer,
	                        boost::asio::transfer_at_least(1),
	                        boost::bind(&SpiderServer::readFromTerminal, this,
	                                    boost::asio::placeholders::error));

	 }

void SpiderServer::readFromTerminal(const boost::system::error_code &error)
{
	if (!error)
	{
		parseInputRequest(Utils::makeStringFromAsioStream(_buffer));

		boost::asio::async_read(_stdIn, _buffer,
		                        boost::asio::transfer_at_least(1),
		                        boost::bind(&SpiderServer::readFromTerminal, this,
		                                    boost::asio::placeholders::error));

	}
	else if (error != boost::asio::error::eof)
	{
		std::cout << __FUNCTION__ <<" error: " << error << "\n";
	}
}

void SpiderServer::parseInputRequest(const std::string &string)
{
	std::cout << __FUNCTION__ << " string : " << string << std::endl;
	//for (auto it = _opCodeDuet.begin(); it < _opCodeDuet.end(); it++)
	{
		//TODO: Get unserialisation to find the opcode
		//if ()
		sendToEveryClient(string);
	}
}
void SpiderServer::tick()
{
	AsioServer::tick();
	queueReadingFromTerminal();
}
