#pragma once
#include <string>
#include <vector>
#include <fstream>

void init();
std::string read(const int LBA, std::ifstream& txtFile);
std::vector<std::string> fullRead();
void write(const std::string& value, const int LBAInt, std::fstream& txtFile);