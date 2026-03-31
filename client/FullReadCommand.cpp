#include "FullReadCommand.h"

int FullReadCommand::operator()() {
	init();
	int errn = 0;
	Errcodes& handler = Errcodes::get();
	if ((errn = validate())) { handler.makeError(errn); return errn; }
	if ((errn = run())) { handler.makeError(errn); return errn; }
	//need result handler?
	return 0;
}
int FullReadCommand::prepare(std::vector<std::string>& args)
{
	cmds = move(args);
	return 0;
}

void FullReadCommand::init()
{
}

int FullReadCommand::run()
{
	ClientHandler& c = ClientHandler::get();
	for (int i = 0; i < 100; i++) {
		std::vector<std::string> cmd = {"read", std::to_string(i)};
		c.send(cmd);
		std::vector<std::string> res = std::move(c.receive());
		std::cout << "LBA " << i << " : ";
		for (auto& s : res) {
			std::cout << s << " ";
		}
		std::cout << std::endl;
	}
	ResultHandler& rs = ResultHandler::get();
	rs.setResult({cmds[0], "1"});
	return 0;
}

int FullReadCommand::validate()
{
	if (cmds.size() != 1) return -1;
	
	return 0;
}
