#include "FullWriteCommand.h"

int FullWriteCommand::operator()() {
	init();
	int errn = 0;
	Errcodes& handler = Errcodes::get();
	if ((errn = validate())) { handler.makeError(errn); return errn; }
	if ((errn = run())) { handler.makeError(errn); return errn; }
	return 0;
}
int FullWriteCommand::prepare(std::vector<std::string>& args)
{
	cmds = std::move(args);
	return 0;
}

void FullWriteCommand::init()
{
}

int FullWriteCommand::run()
{
	ClientHandler& a = ClientHandler::get();

	for (int i = 0; i < 100; i++) {
		a.send(cmds);
		std::vector<std::string> res = std::move(a.receive());
		
	}
	return 0;
}

int FullWriteCommand::validate()
{
	if (cmds.size() != 2) return -1;
	

	std::string& hex = cmds[1];
	if (hex.length() != 10) return -1;
	if (hex[0] != '0' || hex[1] != 'x') return -1;
	for (int i = 2; i < hex.length(); i++) {
		//if (!std::isxdigit(hex[i])) return -1;
		if (!std::isdigit(hex[i]) && ('A' > hex[i] || 'F' < hex[i])) return -1;
	}

	return 0;
}
