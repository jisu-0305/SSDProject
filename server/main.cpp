#include "server.h"
#include <iostream>

int main() {
    try {
        runServer(12345);
    }
    catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}