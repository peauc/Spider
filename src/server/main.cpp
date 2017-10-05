//
// Created by Clément Péau on 04/10/2017.
//

#include <iostream>
#include "AsioServer.hpp"

//TODO:: Programme is able to chose his port with command line

int main()
{
	try
	{
		AsioServer server;

		server.start();
		while(server.shouldRun())
		{
			server.tick();
			sleep(1);
		}
	}
	catch (std::exception &e)
	{
		std::cerr << "Error -> " << e.what() << std::endl;
	}
	return (0);
}
