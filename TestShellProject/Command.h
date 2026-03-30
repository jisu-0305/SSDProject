#pragma once
#include <functional>
#include <vector>
#include <iostream>
#include <sstream>
#include <string>
#include <memory>
#include "ClientHandler.h"
#include "Errcodes.h"
class Command
{
public:
	virtual void operator()() = 0;
	virtual void init() = 0; //err
	virtual int prepare(std::vector<std::string> &args, Errcodes& hander) = 0;
	virtual int validate() = 0;//erro
	virtual int run() = 0; //erro
};

