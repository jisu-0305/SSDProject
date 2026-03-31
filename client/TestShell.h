#pragma once
#include <string>
#include <unordered_map>
#include <functional>
#include <iostream>
#include <tuple>
#include <initializer_list>

#include "Errcodes.h"
#include "ResultHandler.h"


#include "Command.h"
#include "TestCommand.h"
#include "TestAllCommand.h"
#include "HelpCommand.h"
#include "ReadCommand.h"
#include "WriteCommand.h"
#include "FullReadCommand.h"
#include "FullWriteCommand.h"



class TestShell
{
private:
	std::unordered_map<std::string, std::unique_ptr<Command>> commands;
public:
	void init();
	void run();
	std::pair<std::string, std::string> runCommand(std::vector<std::string> cmds, bool inner);
	static TestShell& get();
	bool exists_cmd(std::string cmd);
	int get_valid_cmd_len(std::string cmd);
};

