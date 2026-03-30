#include "TestShell.h"


void TestShell::init() { //open server connection
    commands["read"] = std::make_unique<ReadCommand>();
    commands["write"] = std::make_unique<WriteCommand>();
    //    commands["help"] =
    //    commands["fullwrite"] =
    //    commands["fullread"] =
    commands["test"] = std::make_unique<TestCommand>();
    //commands["TestCommandall"] =
}
void TestShell::run() {
    std::string in;
    std::string temp;

    Errcodes& errhandler = Errcodes::get();
    std::vector<std::string> args;

    std::cout << "installed cmds" << std::endl;
    for (auto& [k, v] : commands) {
        std::cout << k << std::endl;
    }
    while (1) {
        args.clear();
        temp = "";
        std::cout << "shell>";
        std::getline(std::cin, in);

        std::stringstream ss(in);
        while (std::getline(ss, temp, ' ')) {
            args.push_back(temp);
        }

       
        if (args[0] == "exit") break;

        if (!commands.count(args[0])) { //wrong input
            std::cout << "ERROR" << std::endl;
            continue;
        }
        
        
        auto cmd = commands[args[0]].get();
        cmd->prepare(args);
        int ret = 0;
        if ((ret = (*cmd)())) {
            std::cout << errhandler.getErrorMsg() << std::endl;
        }
        //cmd->validate(); //will be called like commands[in]();
        //cmd->run();
        //int err = commands[in]->;
        //handle errcode? or do it in commands class.
    }
}
int main() {
    TestShell ts;
    ts.init();
    ts.run();
}