//
// Created by Clément Péau on 08/10/2017.
//

#ifndef CPP_SPIDER_UTILS_HPP
#define CPP_SPIDER_UTILS_HPP

#include <string>
#include <boost/asio/streambuf.hpp>
#include <sstream>

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
};

#endif //CPP_SPIDER_UTILS_HPP
