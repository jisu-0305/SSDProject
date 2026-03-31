#include "FullReadCommand.h"

int FullReadCommand::operator()() {
	init();
	int errn = 0;
	Errcodes& handler = Errcodes::get();
	ResultHandler& reshandler = ResultHandler::get();

	if ((errn = validate())) { handler.makeError(errn); return errn; }
	if ((errn = run())) { handler.makeError(errn); return errn; }
	reshandler.setResult(cmd_cat, "SUCCESS");
	//need result handler?
	return 0;
}
int FullReadCommand::prepare(std::vector<std::string>& args) //
{
	cmds = move(args);
	cmd_cat = "";
	
	return 0;
}

void FullReadCommand::init() //initial calc
{
	for (auto& s : cmds) {
		cmd_cat += s;
		cmd_cat += " ";
	}
	cmd_cat.pop_back();
}

int FullReadCommand::run()
{
	ClientHandler& c = ClientHandler::get();
	FileHandler& f = FileHandler::get();
	ResultHandler& reshandler = ResultHandler::get();
	TestShell& executor = TestShell::get();
	for (int i = 0; i < 100; i++) {
		std::vector<std::string> cmd = {"read", std::to_string(i)};
		auto result = executor.runCommand(std::vector<std::string>({ "read", std::to_string(i)}), true);
		if (result.second == "ERROR") {
			reshandler.setResult(cmd_cat, "ERROR");
			break;
		}
		std::cout << "LBA " << i << " : " << result.second << std::endl;
		//std::cout << std::endl;
	}
	return 0;
}

int FullReadCommand::validate()
{
	if (cmds.size() != 1) return -2;
	
	return 0;
}
