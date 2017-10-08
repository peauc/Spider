//
// Created by Clément Péau on 08/10/2017.
//

#ifndef CPP_SPIDER_UTILS_HPP
#define CPP_SPIDER_UTILS_HPP

#include <string>
#include <sstream>
#include "client/SpiderClient.hpp"
#include "boost/asio/streambuf.hpp"
#include "boost/archive/text_iarchive.hpp"


class Utils
{
public:
	static std::string makeStringFromAsioStream(boost::asio::streambuf &buffer) {
		std::ostringstream ss;
		std::string string;

		ss << &buffer;
		string = ss.str();
		return (string);
	}


void                                deserialize(t_paquet &data, boost::asio::streambuf &buf)
{
	std::istream is(&buf);
	boost::archive::text_iarchive ar(is);

	ar & data;
}
};

#endif //CPP_SPIDER_UTILS_HPP
