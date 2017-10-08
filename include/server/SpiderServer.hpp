//
// Created by Clément Péau on 27/09/2017.
//

#ifndef CPP_SPIDER_KEYLOGGERSERVER_HPP
#define CPP_SPIDER_KEYLOGGERSERVER_HPP

#include "server/AsioServer.hpp"

class SpiderServer : public AsioServer {
public:
	SpiderServer();
	~SpiderServer();

	void queueReadingFromTerminal();
private:
	void readFromTerminal(const boost::system::error_code &code);
	boost::asio::posix::stream_descriptor _stdIn;
};

#endif //CPP_SPIDER_KEYLOGGERSERVER_HPP
