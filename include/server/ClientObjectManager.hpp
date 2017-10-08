//
// Created by Clément Péau on 06/10/2017.
//

#ifndef CPP_SPIDER_CLIENTOBJECTMANAGER_HPP
#define CPP_SPIDER_CLIENTOBJECTMANAGER_HPP

#include <server/ServerClientObject.hpp>

class ClientObjectManager {
public:
	ClientObjectManager();
	~ClientObjectManager();

	bool addClient(ServerClientObject::shared_ptr &ptr);
	bool kickClient(ServerClientObject::shared_ptr &ptr);

	void printEveryClientBuffer();
	void readOnEveryClient();
	std::vector<std::string>    getEveryClientInput();
	bool sendMessageToClient(ServerClientObject::shared_ptr &client, std::string message);
	bool sendMessageToEveryClient(std::string message);
private:
	std::vector<ServerClientObject::shared_ptr> _clientList;

};

#endif //CPP_SPIDER_CLIENTOBJECTMANAGER_HPP
