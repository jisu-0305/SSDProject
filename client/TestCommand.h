#pragma once
#include "Command.h"
#include "TestShell.h"
class TestCommand : public Command
{
private:
	const int len = 2;
	std::vector<std::string> cmds;
	
public:
	TestCommand();
	int operator() (bool inner) override;
	int prepare(std::vector<std::string>& args) override;
	void init() override;
	int get_valid_len() override {return 2;}
	int run() override;
	int validate() override;
};

