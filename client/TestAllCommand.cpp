#include "TestAllCommand.h"

int TestAllCommand::operator()() {
    init();
    int errn = 0;
    Errcodes& handler = Errcodes::get();
    if ((errn = validate())) { handler.makeError(errn); return errn; }
    if ((errn = run())) { handler.makeError(errn); return errn; }
    return 0;
}

TestAllCommand::TestAllCommand() {}
void TestAllCommand::init() { //상수 설정 (ex cmd length)

}
int TestAllCommand::prepare(std::vector<std::string>& args)
{
    cmds = std::move(args);
    return 0;
}


int TestAllCommand::run()
{
    //read file dir, find filename with given str, then do test
    FileHandler& handler = FileHandler::get();
    std::vector < std::string> targets = handler.getalltest();

    for (auto& s : targets) {
        //std::vector<std::string> cmd = handler.get_test_cmds(s);
        std::vector<std::string> cmd = { "test", s };
        TestShell& executor = TestShell::get();
        auto resultpair = executor.runCommand(cmd, true);
        //if (resultpair.second == res) {
        //    std::cout << "succeed" << std::endl;
        //}
        //else {
        //    std::cout << "error on > " << order << std::endl;
        //}
    }
    return 0;
}

int TestAllCommand::validate()
{
    //TestAllCommand
    //std::cout << "INPUT:  ";
    //for (auto& s : cmds) {
    //    std::cout << s << " " << std::endl;
    //}
    if (cmds.size() != 1) return -2;
    

    return 0;
}