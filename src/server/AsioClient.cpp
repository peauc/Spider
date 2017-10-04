//
// Created by Clément Péau on 27/09/2017.
//

#include "AsioClient.hpp"
#include <boost/bind.hpp>
#include <iostream>
#include <boost/array.hpp>

AsioClient::AsioClient(boost::asio::io_service &io_service, int port): socket(io_service)
{
  this->port = port;
}

AsioClient::~AsioClient()
{

}

void 		AsioClient::try_send(std::string host, int port)
{
  boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::address::from_string(host), port);

  std::string message = "ping";
  int 		i = 0;

  boost::system::error_code ec;
  this->socket.connect(endpoint, ec);
  if (ec)
    std::cout << "error" << std::endl;
  boost::array<char, 1024> buf;
  while (1) {
    i++;
    std::copy(message.begin(), message.end(), buf.begin());
    boost::system::error_code error;
    if (i == 10)
    {
      boost::asio::async_write(socket, boost::asio::buffer(buf),  boost::bind(&AsioClient::handle_read_status_line, this,
                                                                             boost::asio::placeholders::error));
      sleep(3);
      exit(1);
      i = 0;
    }
   // this->socket.write_some(boost::asio::buffer(buf, message.size()), error);
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
  Asiatic.try_send("127.0.0.1", std::stoi(av[1]));
  return 0;
}*/
