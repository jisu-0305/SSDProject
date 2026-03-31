#include "FullWriteCommand.h"

int FullWriteCommand::operator()() {
	init();
	int errn = 0;
	Errcodes& handler = Errcodes::get();
	if ((errn = validate())) { handler.makeError(errn); return errn; }
	if ((errn = run())) { handler.makeError(errn); return errn; }

	ResultHandler& reshandler = ResultHandler::get();
	reshandler.setResult(cmd_cat, "SUCCESS");
	return 0;
}
int FullWriteCommand::prepare(std::vector<std::string>& args)
{
	cmds = std::move(args);
	
	return 0;
}

void FullWriteCommand::init()
{
	cmd_cat = "";
	for (auto& s : cmds) {
		cmd_cat += s;
		cmd_cat += " ";
	}
	cmd_cat.pop_back();
}

int FullWriteCommand::run()
{
	ClientHandler& a = ClientHandler::get();
	ResultHandler& reshandler = ResultHandler::get();
	FileHandler& f = FileHandler::get();
	TestShell& executor = TestShell::get();
	for (int i = 0; i < 100; i++) {
		auto result = executor.runCommand(std::vector<std::string>({ "write", std::to_string(i), cmds[1] }));
		if (result.second == "ERROR") {
			reshandler.setResult(cmd_cat, "ERROR");
			break;
		}
		//std::vector<std::string> res = std::move(a.receive());
		//for (auto& s : res) {
		//	std::cout << s << " ";
		//}
		//std::cout << std::endl;
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
