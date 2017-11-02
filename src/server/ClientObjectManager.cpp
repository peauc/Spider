//
// Created by Clément Péau on 06/10/2017.
//

#include <iostream>
#include "server/ClientObjectManager.hpp"

bool ClientObjectManager::sendMessageToClient(ServerClientObject::shared_ptr &client, std::string message)
{
	auto it = std::find(_clientList.begin(), _clientList.end(), client);
	if (it != _clientList.end())
	{
		it->get()->write(message);
		return (true);
	}
	return (false);
}

bool ClientObjectManager::sendMessageToEveryClient(const std::string message)
{
	for (auto it = _clientList.begin(); it < _clientList.end(); it++)
	{
		it->get()->write(message);
	}
	return (true);
}

void ClientObjectManager::readOnEveryClient()
{
	auto it = _clientList.begin();

	while (it != _clientList.end())
	{
		it->get()->tryReading();
		it++;
	}
}

void ClientObjectManager::printEveryClientBuffer()
{
	for (auto it = _clientList.begin(); it < _clientList.end(); it++)
	{
		std::cout << it - _clientList.begin() << ":" << std::endl << it->get()->getInputBuffer();
	}
}
bool ClientObjectManager::addClient(ServerClientObject::shared_ptr &newClient)
{
	std::cout << "Adding a client" << std::endl;

	_clientList.push_back(newClient);
	return (true);
}
bool ClientObjectManager::kickClient(ServerClientObject::shared_ptr &ptr)
{
	return false;
}

ClientObjectManager::ClientObjectManager()
{
}

ClientObjectManager::~ClientObjectManager()
{
}

std::vector<std::string> ClientObjectManager::getEveryClientInput()
{
	std::vector<std::string>   clientInputList;

	for (auto it = _clientList.begin(); it < _clientList.end(); it++)
	{
		clientInputList.push_back(it->get()->getInputBuffer());
		it->get()->resetInputBuffer();
	}
	return (clientInputList);
}

