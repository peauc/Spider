//
// Created by Clément Péau on 27/09/2017.
//

#include "AsioClient.hpp"
#include <iostream>
#include <boost/array.hpp>

AsioClient::AsioClient(){

}

AsioClient::~AsioClient()
{

}

void 		AsioClient::try_send(std::string host, int port)
{
  boost::asio::io_service ios;

  std::string message = "toto le noichpute";

  boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::address::from_string(host), port);

  boost::asio::ip::tcp::socket socket(ios);

  std::cout << "here" << std::endl;
  boost::system::error_code ec;
  socket.connect(endpoint, ec);
  if (ec)
  {
    std::cout << "error" << std::endl;

  }
  std::cout << "here2" << std::endl;

  boost::array<char, 256> buf;
  std::copy(message.begin(),message.end(),buf.begin());
  std::cout << "here3" << std::endl;
  boost::system::error_code error;
  socket.write_some(boost::asio::buffer(buf, message.size()), error);
  std::cout << "here4" << std::endl;
  socket.close();
}

int main()
{
  AsioClient	Asiatic;

  Asiatic.try_send("127.0.0.1", 4142);
  return 0;
}
