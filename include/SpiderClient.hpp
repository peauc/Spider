//
// Created by Clément Péau on 27/09/2017.
//

#ifndef CPP_SPIDER_KEYLOGGERCLIENT_HPP
#define CPP_SPIDER_KEYLOGGERCLIENT_HPP

#include "AsioClient.hpp"

class SpiderClient : public AsioClient {
public:
	SpiderClient();
	~SpiderClient();
};

#endif //CPP_SPIDER_KEYLOGGERCLIENT_HPP
