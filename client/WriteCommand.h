#pragma once
#include "Command.h"

class WriteCommand : public Command
{
private:
	std::vector<std::string> cmds;
	std::string cmd_cat;
	int no;
public:
	WriteCommand() {};
	int operator() (bool) override;
	int prepare(std::vector<std::string>& args) override;
	void init() override;
	int run() override;
	int validate() override;
	int get_valid_len() override { return 3; };
};

