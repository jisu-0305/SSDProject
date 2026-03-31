#include "TestShell.h"


void TestShell::init() { //open server connection
    commands["read"] = std::make_unique<ReadCommand>();
    commands["write"] = std::make_unique<WriteCommand>();
    commands["help"] = std::make_unique<HelpCommand>();
    commands["fullwrite"] = std::make_unique<FullWriteCommand>();
    commands["fullread"] = std::make_unique<FullReadCommand>();
    commands["test"] = std::make_unique<TestCommand>();
    commands["testall"] = std::make_unique<TestAllCommand>();
}
void TestShell::run() {
    std::string in;
    std::string temp;

    Errcodes& errhandler = Errcodes::get();
    ResultHandler& reshandler = ResultHandler::get();
    std::vector<std::string> args;

    std::cout << "installed cmds" << std::endl;
    for (auto& [k, v] : commands) {
        std::cout << k << " : " << v.get()->get_valid_len() << std::endl;
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

        if (args.empty()) continue;
        if (args[0] == "exit") break;

        if (!commands.count(args[0])) { //wrong input
            std::cout << "INVALID COMMAND" << std::endl;
            continue;
        }
        
        
        auto cmd = commands[args[0]].get();
        cmd->prepare(args);
        int ret = 0;
        if ((ret = (*cmd)())) {
            std::cout << errhandler.getErrorMsg() << std::endl;
        }
        else {
            auto res = reshandler.getResult();
            std::cout << res.second << std::endl;
        }
        //cmd->validate(); //will be called like commands[in]();
        //cmd->run();
        //int err = commands[in]->;
        //handle errcode? or do it in commands class.
    }
}
std::pair<std::string, std::string> TestShell::runCommand(std::vector<std::string> order, bool inner)
{
    ResultHandler& reshandler = ResultHandler::get();
    Errcodes& errhandler = Errcodes::get();
    if (!commands.count(order[0])) {
        errhandler.makeError(-2);
        reshandler.setResult("", errhandler.getErrorMsg());
        return reshandler.getResult();
    }
    auto cmd = commands[order[0]].get();
    cmd->prepare(order);
    int ret = 0;
    if ((ret = (*cmd)()) && !inner) {
        std::cout << errhandler.getErrorMsg() << std::endl;
    }
    return reshandler.getResult();
}
TestShell& TestShell::get() {
    static TestShell ts;
    return ts;
}
bool TestShell::exists_cmd(std::string cmd)
{
    return (!commands.count(cmd)) ? false : true;
}
int TestShell::get_valid_cmd_len(std::string cmd) {
    if (!exists_cmd(cmd)) return -1;
    return commands[cmd].get()->get_valid_len();
}
int main() {
    TestShell& ts = TestShell::get();
    ts.init();
    ts.run();
}