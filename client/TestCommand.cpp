#include "TestCommand.h"

int TestCommand::operator()() {
    /**
    * 
    */
    //int res = 
    return 0;
}

TestCommand::TestCommand() {
    init();
}
void TestCommand::init() { //상수 설정 (ex cmd length)

}
int TestCommand::prepare(std::vector<std::string>& args)
{
    cmds = std::move(args);
    return 0;
}


int TestCommand::run()
{

    return 0;
}

int TestCommand::validate()
{
    //TestCommand
    std::cout << "INPUT:  ";
    for (auto& s : cmds) {
        std::cout << s << " " << std::endl;
    }
    if (cmds.size() > len) return -1;
    std::string& s = cmds[0];

    if (!std::isdigit(s[0])) return -1;
    if (s[1] != '_') return -1;
    
    
    return 0;
}