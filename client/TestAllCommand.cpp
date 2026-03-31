#include "TestAllCommand.h"

int TestAllCommand::operator()() {
    init();
    int errn = 0;
    Errcodes& handler = Errcodes::get();
    if ((errn = validate())) { handler.makeError(errn); return errn; }
    if ((errn = run())) { handler.makeError(errn); return errn; }
    return 0;
}

TestAllCommand::TestAllCommand() {
    init();
}
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
    return 0;
}

int TestAllCommand::validate()
{
    //TestAllCommand
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