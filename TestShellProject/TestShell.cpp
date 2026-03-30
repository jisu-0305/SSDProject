#include "TestShell.h"


void TestShell::init() { //open server connection
    //commands["read"] =
    //    commands["write"] =
    //    commands["help"] =
    //    commands["fullwrite"] =
    //    commands["fullread"] =
    commands["test"] = std::make_unique<TestCommand>();
    //commands["TestCommandall"] =
}
void TestShell::run() {
    std::string in;
    Errcodes errhandler;
    while (1) {
        std::cout << "shell>";
        std::cin >> in;

        if (in == "exit") break;

        if (!commands.count(in)) { //wrong input

            continue;
        }
        
        commands[in]();
        //int err = commands[in]->;
        //handle errcode? or do it in commands class.
    }
}
int main() {
    TestShell ts;
    ts.init();
    ts.run();
}