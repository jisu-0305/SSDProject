#pragma once
#include <string>
#include <memory>
#include <vector>
#include <boost/asio.hpp>
#include <iostream>

using boost::asio::ip::tcp;

class ClientHandler
{
private:
	std::unique_ptr<boost::asio::io_context> io;
	std::unique_ptr<tcp::socket> socket;
	ClientHandler();
	bool debug;
public:
	static ClientHandler& get();
	int send(std::vector<std::string>&);
	std::vector<std::string> receive();
};