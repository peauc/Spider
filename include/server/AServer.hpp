//
// Created by Clément Péau on 27/09/2017.
//

#ifndef CPP_SPIDER_SERVER_HPP
#define CPP_SPIDER_SERVER_HPP

class AServer {
public:
	virtual bool run() = 0;
	virtual bool stop() = 0;
	virtual ~Server() = 0;
private:
};

#endif //CPP_SPIDER_SERVER_HPP
