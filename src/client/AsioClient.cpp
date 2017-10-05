//
// Created by Clément Péau on 27/09/2017.
//

#include <boost/bind.hpp>
#include <iostream>
#include <boost/array.hpp>
#include "AsioClient.hpp"
#include "Command.h"


AsioClient::AsioClient(boost::asio::io_service &io_service, int port): socket(io_service)
{
  this->port = port;
}

AsioClient::~AsioClient()
{

}

void 		AsioClient::try_send(std::string host)
{
  boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::address::from_string(host), this->port);
  Command		command;
  std::string 		message;
  boost::system::error_code ec;
  boost::system::error_code error;
  std::ostringstream 	ss;

  this->socket.connect(endpoint, ec);
  if (ec)
    std::cout << "error" << std::endl;
  boost::array<char, 2048> buf;
  while (1) {
    boost::asio::async_read(socket, response,
			    boost::asio::transfer_at_least(1),
			    boost::bind(&AsioClient::handle_read_content, this,
					boost::asio::placeholders::error));
    ss << response;
    if (NULL != (message = command.process(this->modules, ss.str())))
	{
	  std::copy(message.begin(), message.end(), buf.begin());
	  boost::asio::async_write(socket, boost::asio::buffer(buf),
				   boost::bind(&AsioClient::handle_read_status_line,
					       this, boost::asio::placeholders::error));
	}
	/*else
	  error();*/



  }
  this->socket.close();
}

/*int main(int ac, char **av)
{
  boost::asio::io_service io_service;
  io_service.run();

  if (ac != 2)
  {
    std::cout << "Usage: ./client <port>" << std::endl;
    return 0;
  }
  AsioClient	Asiatic(io_service, std::stoi(av[1]));
  Asiatic.try_send("127.0.0.1");
  return 0;
}*/
