#include "validator.h"
#include <stdexcept>

int transformInt(std::string& s) {
    if (s.size() > 2) return -1;
    try {
        int LBAInt = std::stoi(s);
        if (0 <= LBAInt && LBAInt < 100) return LBAInt;
        else return -1;
    }
    catch (const std::invalid_argument&) {
        return -1;
    }
}

bool isValidValue(const std::string& s) {
    if (s.size() != 10) return false;
    if (s.substr(0, 2) != "0x") return false;
    for (int i = 2; i < 10; i++) {
        char c = s[i];
        if ((48 <= c && c <= 57) || (65 <= c && c <= 70)) continue;
        else return false;
    }
    return true;
}