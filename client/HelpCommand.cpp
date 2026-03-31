#include "HelpCommand.h"



void HelpCommand::HelpCommand() {
	std::cout << "팀 이름: 쌀먹 삼대장";
	std::cout << "팀  원: 이민한, 김지수, 오승훈 ";
	std::cout << "각 명령어 사용 법";

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

}