//
// Created by Clément Péau on 27/09/2017.
//

#include <iostream>
#include "AsioServer.hpp"

AsioServer::AsioServer()
{
	try
	{
		_ioService.run();
	}
	catch(std::exception &exception)
	{
		std::cerr << exception.what() << std::endl;
	}

}

AsioServer::~AsioServer()
{

}
