#include "WriteCommand.h"

int WriteCommand::operator()() {
	init();
	int errn = 0;
	Errcodes& handler = Errcodes::get();
	if ((errn = validate())) { handler.makeError(errn); return errn; }
	if ((errn = run())) { handler.makeError(errn); return errn; }
	return 0;
}
int WriteCommand::prepare(std::vector<std::string>& args)
{
	cmds = std:: move(args);
	return 0;
}

void WriteCommand::init()
{
	no = -1;
}

int WriteCommand::run()
{
	ClientHandler &a = ClientHandler::get();

	a.send(cmds);
	return 0;
}

int WriteCommand::validate()
{
	if (cmds.size() != 3) return -1;
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

	std::string& hex = cmds[2];
	if (hex.length() != 10) return -1;
	if (hex[0] != '0' || hex[1] != 'x') return -1;
	for (int i = 2; i < hex.length(); i++) {
		//if (!std::isxdigit(hex[i])) return -1;
		if (!std::isdigit(hex[i]) && ('A' > hex[i] || 'F' < hex[i])) return -1;
	}

	return 0;
}
