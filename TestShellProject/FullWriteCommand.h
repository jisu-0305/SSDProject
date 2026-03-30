#pragma once
#include "Command.h"
class FullWriteCommand : public Command
{
private:
	const int len = 2;
	std::vector<std::string> cmds;

public:
	FullWriteCommand();
	void operator() () override;
	int prepare(std::vector<std::string>& args, Errcodes& handler) override;
	void init() override;
	int run() override;
	int validate() override;
};

