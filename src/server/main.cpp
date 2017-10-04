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

		server.run();
	}
	catch (std::exception &e)
	{
		std::cerr << "Error -> " << e.what() << std::endl;
	}
	while (1);
	return (0);
}
