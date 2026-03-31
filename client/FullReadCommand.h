#pragma once
#include "Command.h"
#include "TestShell.h"
class FullReadCommand : public Command
{
private:
	const int len = 2;
	std::vector<std::string> cmds;
	std::string cmd_cat;
public:
	FullReadCommand() {};
	int operator()() override;
	int prepare(std::vector<std::string>& args) override;
	void init() override;
	int run() override;
	int validate() override;
	int get_valid_len() override { return 1; }
};

