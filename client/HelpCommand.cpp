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
    //std::cout << "INPUT:  ";
    //for (auto& s : cmds) {
    //    std::cout << s << " " << std::endl;
    //}
    if (cmds.size() != 1) return -2;

    return 0;
}

int HelpCommand::run()
{
    std::cout << "팀 이름: 쌀먹 삼대장 ";
	std::cout << "팀  원: 이민한, 김지수, 오승훈 ";
	std::cout << "각 명령어 사용 법 "; 

	std::cout << "[Write]: write 숫자 value를 넣으세요 ex): write 3 0x11223344" << std::endl;
	std::cout << "\n";
	std::cout<<"[Read]: write 숫자를 넣으세요 ex): read 3" << std::endl;
	std::cout << "\n";
	std::cout<<"[exit]: exit을 넣으세요 ex): exit" << std::endl;
	std::cout << "\n";
	std::cout<<"[help]: help를 넣으세요 ex): help" << std::endl;
	std::cout << "\n";
	std::cout<<"[fullwrite]: fullwrite value를 넣으세요 ex): fullwrite 0x11223344"<< std::endl;
	std::cout << "\n";
	std::cout<<"[fullread]: fullread를 넣으세요 ex): fullread" << std::endl;
	std::cout << "\n";
	std::cout<<"[test]: test 테스트이름을 넣으세요 ex): test 1_FullReadTest" << std::endl;
	std::cout << "\n";
	std::cout<<"[testall]: testall을 넣으세요 ex): testall" << std::endl;

    //read file dir, find filename with given str, then do test
    return 0;
}
