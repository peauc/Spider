//
// Created by Clément Péau on 27/09/2017.
//

#ifndef CPP_SPIDER_ASIOCLIENT_HPP
#define CPP_SPIDER_ASIOCLIENT_HPP

#include <boost/asio.hpp>
#include <iostream>
#include "client/AClient.hpp"
#include "client/Command.hpp"

class Module;

class AsioClient : public AClient {
public:
	AsioClient(boost::asio::io_service &, unsigned short);
	~AsioClient();
  void	try_send(const std::string);
  void 	handle_read_state(const boost::system::error_code&);
  void 	handle_read_h(const boost::system::error_code&);
  void 	handle_read_body(const boost::system::error_code&);
  bool 	stop(const std::string) const;
 private:
  unsigned short			port;
  boost::asio::ip::tcp::socket 		socket;
  boost::asio::streambuf 		answer;
  std::map<char, Module>		modules;
};

#endif //CPP_SPIDER_ASIOCLIENT_HPP
