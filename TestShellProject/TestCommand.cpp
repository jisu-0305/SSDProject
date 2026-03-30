#include "TestCommand.h"


void TestCommand::init() {

}
int TestCommand::prepare()
{
    cmds.clear();
    //splice

    std::string in;
    std::string temp;
    std::getline(std::cin, in);
    std::stringstream ss(in);
    while (std::getline(ss, temp, ' ')) {
        cmds.push_back(temp);
    }
    int valres = validate();
    if (!valres) return valres;
    int runres = run();
    return runres;
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
    if (cmds.size() > len - 1) return -1;
    std::string& s = cmds[0];

    if (!std::isdigit(s[0])) return -1;
    if (s[1] != '_') return -1;
    
    
    return 0;
}