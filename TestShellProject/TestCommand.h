#pragma once
#include "Command.h"
class TestCommand : public Command
{
private:
	std::unique_ptr<TestCommand> value;
	const int len =2;
	std::vector<std::string> cmds;
	TestCommand() {};
public:
	int prepare() override;
	void init() override;
	int run() override;
	int validate() override;
};

