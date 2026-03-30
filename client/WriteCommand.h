#pragma once
#include "Command.h"

class WriteCommand : public Command
{
private:
	std::vector<std::string> cmds;
	int no;
public:
	WriteCommand() {};
	int operator() () override;
	int prepare(std::vector<std::string>& args) override;
	void init() override;
	int run() override;
	int validate() override;
};

