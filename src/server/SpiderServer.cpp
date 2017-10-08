//
// Created by Clément Péau on 27/09/2017.
//

#include "server/SpiderServer.hpp"
#include <iostream>

SpiderServer::SpiderServer() : _stdIn(getIoService())
{
	std::cout << "SpiderServer is launching" << std::endl;
}

SpiderServer::~SpiderServer()
{

}

void SpiderServer::queueReadingFromTerminal()
{
	/*boost::asio::async_read(_socket, _buffer,
	                        boost::asio::transfer_at_least(1),
	                        boost::bind(&ServerClientObject::readContentHandler, this,
	                                    boost::asio::placeholders::error));
     */
	 }

void SpiderServer::readFromTerminal(const boost::system::error_code &code)
{

}
