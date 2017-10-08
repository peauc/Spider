//
// Created by Clément Péau on 27/09/2017.
//

#include "server/Utils.hpp"
#include "server/SpiderServer.hpp"
#include <iostream>
#include <string>

SpiderServer::SpiderServer() :
		_stdIn(getIoService()),
		_opCodeDuet (std::vector<std::pair<char, std::string>> { {0x10, "SendKb"}, {0x11, "SendMo"}, {0x12, "SendSs"} })
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
	for (auto it = _opCodeDuet.begin(); it <= _opCodeDuet.end(); it++)
	{
		try
		{
			if (string.find(it->second) != std::string::npos)
				sendToEveryClient(std::string(1, it->first));
		}
		catch (std::exception &e)
		{
			std::cerr << e.what() << std::endl;
		}
	}
}
void SpiderServer::tick()
{
	std::vector<std::string>    clientInputList;

	AsioServer::tick();
	queueReadingFromTerminal();
	clientInputList = getClientObjectManager().getEveryClientInput();
	for (auto it = clientInputList.begin(); it < clientInputList.end(); it++)
	{
		if (!it->empty())
		{
			t_paquet    paquet;
			boost::asio::streambuf sb;
			std::iostream       ioStream(&sb);

			ioStream << *it;
			paquet = Utils::deserialize(sb);
			std::cout << paquet.toString() << std::endl;
		}
	}
}
