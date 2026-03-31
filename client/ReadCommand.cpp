#include "ReadCommand.h"

int ReadCommand::operator()() {
	init();
	int errn = 0;
	Errcodes& handler = Errcodes::get();
	ResultHandler& reshandler = ResultHandler::get();
	if ((errn = validate())) { 
		reshandler.setResult(cmd_cat, handler.getErrorMsg());
		handler.makeError(errn); 
		return errn;
	}
	if ((errn = run())) { 
		handler.makeError(errn);
		reshandler.setResult(cmd_cat, handler.getErrorMsg());
		return errn; 
	}
	//reshandler.setResult(cmds[0] + " " + cmds[1], res[0]);
	return 0;
}
int ReadCommand::prepare(std::vector<std::string>& args)
{
	cmds = move(args);
	cmd_cat = "";
	
	return 0;
}

void ReadCommand::init()
{
	for (auto& s : cmds) {
		cmd_cat += s;
		cmd_cat += " ";
	}
	cmd_cat.pop_back();
	no = -1;
}

int ReadCommand::run()
{
	ClientHandler& c = ClientHandler::get();
	c.send(cmds);
	std::vector<std::string> res = std::move(c.receive());
	//for (auto& s : res) {
	//	std::cout << s << " ";
	//}
	ResultHandler& reshandler = ResultHandler::get();

	reshandler.setResult(cmd_cat, "0x" + res[0]);
	//std::cout << std::endl;
	return 0;
}

int ReadCommand::validate()
{
	if (cmds.size() != 2) return -2;
	std::string& target = cmds[1];
	std::stringstream ss(target);
	int num = 0;
	if (ss >> num) {
		if (num < 0 || num >= 100) return -1; // outof rang
	}
	else {
		return -1;
	}
	no = num;
	return 0;
}
