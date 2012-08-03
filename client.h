#pragma once

#include <boost/asio.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/shared_ptr.hpp>
#include "service.h"

using boost::asio::ip::tcp;

class client : public boost::enable_shared_from_this<client>
{
public:
	client(boost::asio::io_service& io_service);
	~client(void);

	tcp::socket& socket()
	{
		return socket_;
	}

	void setStop(boost::function<void(boost::shared_ptr<client>)> _stop);
	void start();
	void stop();
	void write(char *data, size_t size);
	void setService(boost::shared_ptr<service> ptr)
	{
		service_ptr_ = ptr;
	}

private:
	void handle_read(const boost::system::error_code& error, size_t bytes_transferred);
	void handle_write(const boost::system::error_code& error);
	//void handle_read_server(const boost::system::error_code& error,	size_t bytes_transferred);
	//void handle_write_server(const boost::system::error_code& error);

	enum { max_length = 1024 };
	char data_[max_length];
	int recv_count;	//���մ���
	boost::shared_ptr<service> service_ptr_;
	boost::function<void(boost::shared_ptr<client>)> stop_;

public:
	tcp::socket socket_;
};