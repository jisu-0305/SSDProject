#include "TestCommand.h"

int TestCommand::operator()() {
    init();
    int errn = 0;
    Errcodes& handler = Errcodes::get();
    if ((errn = validate())) { handler.makeError(errn); return errn; }
    if ((errn = run())) { handler.makeError(errn); return errn; }
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
    //read file dir, find filename with given str, then do test
    FileHandler &filehandler = FileHandler::get();
    std::string target_case = filehandler.getrelevant(cmds[1]);
    std::vector<std::string> orders = filehandler.get_test_cmds(target_case);
    std::vector<std::string> shards;
    std::string shard;
    for (auto& order: orders) {
        
        std::cout << "taking " << order << std::endl;
        std::stringstream ss(order);
        while (std::getline(ss, shard, ' ')) {
            shards.emplace_back(shard);
        }
        
        std::string cmd = 
        std::string res = shards.back();

        TestShell::get();
    }
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
    std::string& s = cmds[1];

    if (!std::isdigit(s[0])) return -1;
    if (s[1] != '_') return -1;
    
    
    return 0;
}