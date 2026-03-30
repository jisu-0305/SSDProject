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
    std::string temp;

    Errcodes errhandler;
    std::vector<std::string> args;

    while (1) {
        //args.clear();
        temp = "";
        std::cout << "shell>";
        std::getline(std::cin, in);

        std::stringstream ss(in);
        while (std::getline(ss, temp, ' ')) {
            args.push_back(temp);
        }
        if (args[0] == "exit") break;

        if (!commands.count(args[0])) { //wrong input
            continue;
        }
        
        
        auto& cmd = commands[in];
        cmd->prepare(args, errhandler);
        cmd->validate();
        cmd->run();
        //int err = commands[in]->;
        //handle errcode? or do it in commands class.
    }
}
int main() {
    TestShell ts;
    ts.init();
    ts.run();
}