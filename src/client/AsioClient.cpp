//
// Created by Clément Péau on 27/09/2017.
//

#include <boost/bind.hpp>
#include <iostream>
#include <boost/array.hpp>
#include "client/AsioClient.hpp"
#include "client/Command.hpp"


std::string answer_to_string( boost::asio::streambuf &answer)
{
  std::string	res;
  std::istream bufs(&answer);

  bufs >> res;
  return res;
}

bool 		AsioClient::stop(const std::string msg) const
{
  if (msg == "exit")
    return true;
  return false;
}

AsioClient::AsioClient(boost::asio::io_service &io_service, unsigned short port): socket(io_service)
{
  this->port = port;
}

AsioClient::~AsioClient()
{

}

void 		AsioClient::try_send(const std::string host)
{
  boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::address::from_string(host), this->port);
  std::string 			message;
  boost::system::error_code 	err;
  boost::asio::streambuf	f_buf;
  boost::system::error_code 	error;
  Command			command;

  this->socket.connect(endpoint, err);
  if (err)
    std::cout << "error" << std::endl;
  boost::array<char, 2048> buf;
  while (1) {
    boost::asio::async_read(socket, answer,
			    boost::asio::transfer_at_least(1),
			    boost::bind(&AsioClient::handle_read_body, this,
					boost::asio::placeholders::error));
    message = answer_to_string(answer);
    if (this->stop(message))
      return ;
    if (command.process(this->modules, "!", f_buf))
	{
	  std::copy(message.begin(), message.end(), buf.begin());
	  boost::asio::async_write(socket, boost::asio::buffer(f_buf.data()),
				   boost::bind(&AsioClient::handle_read_state,
					       this, boost::asio::placeholders::error));
	}
/*	else
	  error();*/
    //exit(0);

  }
  this->socket.close();
}

int main(int ac, char **av)
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
}
