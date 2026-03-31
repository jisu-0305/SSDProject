#pragma once
#include "Command.h"
#include "TestShell.h"
class TestAllCommand : public Command
{
private:
	const int len = 2;
	std::vector<std::string> cmds;
public:
	TestAllCommand();
	int operator() () override;
	int prepare(std::vector<std::string>& args) override;
	void init() override;
	int run() override;
	int validate() override;
};

