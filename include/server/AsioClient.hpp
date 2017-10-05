//
// Created by Clément Péau on 27/09/2017.
//

#ifndef CPP_SPIDER_ASIOCLIENT_HPP
#define CPP_SPIDER_ASIOCLIENT_HPP

#include "AClient.hpp"
#include <boost/asio.hpp>
#include <iostream>
#include "Module.h"

class AsioClient : public AClient {
public:
	AsioClient(boost::asio::io_service &io_service, int port);
	~AsioClient();
  void	try_send(std::string);
  //void 	handle_write_request(const boost::system::error_code err);
  void 	handle_read_status_line(const boost::system::error_code& err);
  void 	handle_read_headers(const boost::system::error_code& err);
  void 	handle_read_content(const boost::system::error_code& err);
 private:
  int 					port;
  boost::asio::ip::tcp::socket 		socket;
  boost::asio::streambuf 		response;
  std::map<char, Module>		modules;
};

#endif //CPP_SPIDER_ASIOCLIENT_HPP
