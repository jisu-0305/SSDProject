#pragma once
#include <string>
#include <unordered_map>
#include <functional>
#include <iostream>
#include "Errcodes.h"
#include "Command.h"
#include "TestCommand.h"

class TestShell
{
private:
	std::unordered_map<std::string, std::unique_ptr<Command>> commands;
public:
	void init();
	void run();
};

