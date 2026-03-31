#pragma once
#include <string>
#include <filesystem>
#include <fstream>
#include <iostream>
#include "Errcodes.h"
namespace fs = std::filesystem;

class FileHandler
{
private:
	bool debug;
	std::ofstream ofs;
public:
	FileHandler() { debug = true; ofs = std::ofstream("output.txt"); }
	static FileHandler& get();
	std::vector<std::string> getalltest();
	std::string getrelevant(std::string shard);
	std::vector<std::string> get_test_cmds(std::string path);
	int writelog(std::string);
};

