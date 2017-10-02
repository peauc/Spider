//
// Created by Clément Péau on 27/09/2017.
//

#ifndef CPP_SPIDER_ASIOCLIENT_HPP
#define CPP_SPIDER_ASIOCLIENT_HPP

#include "AClient.hpp"
#include <boost/asio.hpp>

class AsioClient : public AClient {
public:
	AsioClient();
	~AsioClient();
  void	try_send(std::string, int);
 private:
  /*int 					port;
  boost::asio::io_service		ios;
  boost::asio::ip::tcp::socket		socket(ios);
  boost::asio::ip::tcp::endpoint 	endpoint(boost::asio::ip::address::from_string(std::string), int)*/
};

#endif //CPP_SPIDER_ASIOCLIENT_HPP
