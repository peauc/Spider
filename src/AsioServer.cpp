//
// Created by Clément Péau on 27/09/2017.
//

#include "AsioServer.hpp"

AsioServer::AsioServer()
{
	_io_service.run();

}
AsioServer::~AsioServer()
{

}
