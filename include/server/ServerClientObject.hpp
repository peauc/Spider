//
// Created by Clément Péau on 04/10/2017.
//

#ifndef CPP_SPIDER_SERVERCLIENTOBJECT_HPP
#define CPP_SPIDER_SERVERCLIENTOBJECT_HPP

#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>

class ServerClientObject : public boost::enable_shared_from_this<ServerClientObject>
{
public:
	typedef boost::shared_ptr<ServerClientObject> shared_ptr;

	static shared_ptr create(boost::asio::io_service &io_service);

	boost::asio::ip::tcp::socket &getSocket();

	// Call boost::asio::async_write() to serve the data to the ServerClientObject.
	// We are using boost::asio::async_write(),
	// rather than ip::tcp::get_socket::async_write_some(),
	// to ensure that the entire block of data is sent.

	void start();
private:
	explicit ServerClientObject(boost::asio::io_service &io_service) : _socket(io_service) {}
	// handle_write() is responsible for any further actions
	// for this ServerClientObject connection.
	void handle_write(const boost::system::error_code & /*error*/, size_t /*bytes_transferred*/);

	boost::asio::ip::tcp::socket _socket;
	std::string m_message;
};


#endif //CPP_SPIDER_SERVERCLIENTOBJECT_HPP
