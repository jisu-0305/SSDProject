#include "HelpCommand.h"

int HelpCommand::operator()() {
    init();
    int errn = 0;
    Errcodes& handler = Errcodes::get();
    if ((errn = validate())) { handler.makeError(errn); return errn; }
    if ((errn = run())) { handler.makeError(errn); return errn; }
    return 0;
}

HelpCommand::HelpCommand() {
    init();
}
int HelpCommand::prepare(std::vector<std::string>& args)
{
    cmds = std::move(args);
    return 0;
}
void HelpCommand::init() { //상수 설정 (ex cmd length)

}

int HelpCommand::validate()
{
    //HelpCommand
    std::cout << "INPUT:  ";
    for (auto& s : cmds) {
        std::cout << s << " " << std::endl;
    }
    if (cmds.size() != 1) return -1;

    return 0;
}

int HelpCommand::run()
{
    //read file dir, find filename with given str, then do test
    return 0;
}
