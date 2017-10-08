//
// Created by Clément Péau on 04/10/2017.
//

#include <iostream>
#include <server/SpiderServer.hpp>
#include "server/AsioServer.hpp"

//TODO:: Programme is able to chose his port with command line

int main()
{
	try
	{
		SpiderServer server;

		server.start();
		while(server.shouldRun())
		{
			server.tick();
		}
	}
	catch (std::exception &e)
	{
		std::cerr << "Error -> " << e.what() << std::endl;
	}
	return (0);
}
