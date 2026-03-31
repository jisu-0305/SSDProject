#pragma once
#include <string>
#include <tuple>
#include <initializer_list>

class ResultHandler
{
private:
	std::string order;
	std::string result;
public:
	static ResultHandler& get();
	void setResult(std::string order, std::string res);
	std::pair<std::string, std::string> getResult();
};

