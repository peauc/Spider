//
// Created by thauvi_a on 10/4/17.
//

#include <iostream>
#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <boost/filesystem.hpp>
#include <boost/bind.hpp>
#include "AsioClient.hpp"


void	AsioClient::handle_write_request(const boost::system::error_code err)
{
  if (!err)
  {
    boost::asio::async_read(socket, response,
				  boost::bind(&AsioClient::handle_read_status_line, this,
					      boost::asio::placeholders::error));
  }
  else
  {
    std::cout << "Error: " << err.message() << "\n";
  }
}

void AsioClient::handle_read_status_line(const boost::system::error_code& err)
{
  if (!err)
  {
    std::istream response_stream(&response);
    std::string http_version;
    response_stream >> http_version;
    unsigned int status_code;
    response_stream >> status_code;
    std::string status_message;
    std::getline(response_stream, status_message);
    boost::asio::async_read(socket, response,
				  boost::bind(&AsioClient::handle_read_headers, this,
					      boost::asio::placeholders::error));
  }
  else
  {
    std::cout << "Error: " << err << "\n";
  }
}

void AsioClient::handle_read_headers(const boost::system::error_code& err)
{
  if (!err)
  {
    std::istream response_stream(&response);
    std::string header;
    while (std::getline(response_stream, header) && header != "\n")
      std::cout << header << "\n";
    std::cout << "\n";
    if (response.size() > 0)
      std::cout << &response;
    boost::asio::async_read(socket, response,
			    boost::asio::transfer_at_least(1),
			    boost::bind(&AsioClient::handle_read_content, this,
					boost::asio::placeholders::error));
  }
  else
  {
    std::cout << "Error: " << err << "\n";
  }
}

void AsioClient::handle_read_content(const boost::system::error_code& err)
{
  if (!err)
  {
    std::cout << &response;
    boost::asio::async_read(socket, response,
			    boost::asio::transfer_at_least(1),
			    boost::bind(&AsioClient::handle_read_content, this,
					boost::asio::placeholders::error));
  }
  else if (err != boost::asio::error::eof)
  {
    std::cout << "Error: " << err << "\n";
  }
}