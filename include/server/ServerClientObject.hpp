//
// Created by Clément Péau on 04/10/2017.
//

#ifndef CPP_SPIDER_SERVERCLIENTOBJECT_HPP
#define CPP_SPIDER_SERVERCLIENTOBJECT_HPP


#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>
#include <boost/bind.hpp>

class ServerClientObject : public boost::enable_shared_from_this<ServerClientObject>
{
public:
	typedef boost::shared_ptr<ServerClientObject> shared_ptr;
	static shared_ptr create(boost::asio::io_service &io_service);
	boost::asio::ip::tcp::socket &getSocket();
	void tryReading();

	void resetInputBuffer();
	void write(const std::string &string);
	std::string   getInputBuffer();
	void start();
private:
	explicit ServerClientObject(boost::asio::io_service &io_service) : _socket(io_service) {}
	void handle_write(const boost::system::error_code & /*error*/, size_t /*bytes_transferred*/);
	void readContentHandler(const boost::system::error_code &errors);

	std::ostringstream           _inputBuffer;
	boost::asio::streambuf      _buffer;
	boost::asio::ip::tcp::socket _socket;
	std::string m_message;
};


#endif //CPP_SPIDER_SERVERCLIENTOBJECT_HPP
