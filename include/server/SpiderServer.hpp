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
	void tick() final;
private:
	void parseInputRequest(const std::string &string);
	void readFromTerminal(const boost::system::error_code &error);
	boost::asio::posix::stream_descriptor                   _stdIn;
	boost::asio::streambuf                                  _buffer;
	std::vector<std::pair<char, std::string>>               _opCodeDuet;
};

#endif //CPP_SPIDER_KEYLOGGERSERVER_HPP
