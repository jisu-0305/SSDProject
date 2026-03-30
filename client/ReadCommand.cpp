#include "ReadCommand.h"

int ReadCommand::operator()() {
	init();
	int errn = 0;
	Errcodes& handler = Errcodes::get();
	if ((errn = validate())) { handler.makeError(errn); return errn; }
	if ((errn = run())) { handler.makeError(errn); return errn; }
	return 0;
}
int ReadCommand::prepare(std::vector<std::string>& args)
{
	cmds = move(args);
	return 0;
}

void ReadCommand::init()
{
	no = -1;
}

int ReadCommand::run()
{
	ClientHandler& c = ClientHandler::get();
	c.send(cmds);
	std::vector<std::string> res = std::move(c.receive());
	return 0;
}

int ReadCommand::validate()
{
	if (cmds.size() != 2) return -1;
	std::string& target = cmds[1];
	std::stringstream ss(target);
	int num = 0;
	if (ss >> num) {
		if (num < 0 || num >= 100) return -2; // outof rang
	}
	else {
		return -1;
	}
	no = num;
	return 0;
}
