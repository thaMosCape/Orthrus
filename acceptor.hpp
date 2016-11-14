#pragma once
#include <memory>
#include <boost/asio.hpp>
#include <thread>
#include <unordered_set>
#include <map>
#include "peer.hpp"



class Acceptor
{
private:
	unsigned short port;

	std::shared_ptr<boost::asio::ip::tcp::acceptor> acceptor;

	boost::asio::ip::tcp::endpoint ep;

	std::unique_ptr<std::thread> writer_thread;

	std::string name = "anonymous";

	std::map<std::string, std::shared_ptr<Peer>> peers;


	void init(void);

	void accept_handler(const boost::system::error_code& error,
		std::shared_ptr<boost::asio::ip::tcp::socket> sock);

	void handshake(std::shared_ptr<boost::asio::ip::tcp::socket> sock);

	void msg_proc(void);


public:
	Acceptor(std::shared_ptr<boost::asio::io_service> io_service);

	void start(void);

	void connect(std::string);

	void share_peers(std::shared_ptr<boost::asio::ip::tcp::socket> target);

	void read_peers(std::shared_ptr<boost::asio::ip::tcp::socket> sock);
};