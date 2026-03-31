#include "nand_storage.h"
#include "constants.h"
#include <iostream>

void init() {
    std::ofstream newwrite;
    newwrite.open(FILE_NAME);
    for (int i = 0; i < TOTAL_LBA; i++) {
        std::string temp = "00000000";
        if (i != 99) temp += "\n";
        newwrite.write(temp.c_str(), temp.size());
    }
}

std::string read(const int LBA, std::ifstream& txtFile) {
    std::string line;
    int currentLine = 0;
    if (txtFile.is_open()) {
        while (std::getline(txtFile, line)) {
            if (currentLine == LBA) {
                txtFile.close();
                return line;
            }
            currentLine++;
        }
    }
    return "ERROR";
}

std::vector<std::string> fullRead() {
    std::vector<std::string> data(TOTAL_LBA, "00000000");
    std::ifstream fin(FILE_NAME);
    for (int i = 0; i < TOTAL_LBA; i++) {
        std::getline(fin, data[i]);
    }
    return data;
}

void write(const std::string& value, const int LBAInt, std::fstream& txtFile) {
    auto data = fullRead();
    std::string dataValue = value.substr(2, 8);
    data[LBAInt] = dataValue;
    std::ofstream fout(FILE_NAME);
    for (auto v : data) {
        fout << v << "\n";
    }
}