#pragma once
#include <string>
#include <memory>
#include <vector>
class ClientHandler
{
public:
	int send(std::string &target);
	std::unique_ptr<std::vector<std::string>> receive();
};

