#pragma once
#include "Command.h"
class ReadCommand : public Command
{
private:
	int no;
	std::vector<std::string> cmds;
	std::string cmd_cat;
public:
	ReadCommand() {};
	int operator() () override;
	int prepare(std::vector<std::string>& args) override;
	void init() override;
	int run() override;
	int validate() override;
};

