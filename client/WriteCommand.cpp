#include "WriteCommand.h"

int WriteCommand::operator()() {
	init();
	int errn = 0;
	Errcodes& handler = Errcodes::get();
	ResultHandler& reshandler = ResultHandler::get();
	if ((errn = validate())) {
		reshandler.setResult(cmd_cat, "ERROR");
		handler.makeError(errn);
		return errn;
	}
	if ((errn = run())) {
		handler.makeError(errn);
		reshandler.setResult(cmd_cat, "ERROR");
		return errn;
	}
	reshandler.setResult(cmd_cat, "SUCCESS");
	return 0;
}
int WriteCommand::prepare(std::vector<std::string>& args)
{
	cmds = std::move(args);
	no = -1;
	cmd_cat = "";
	
	return 0;
}

void WriteCommand::init()
{
	for (auto& s : cmds) {
		cmd_cat += s;
		cmd_cat += " ";
	}
	cmd_cat.pop_back();
}

int WriteCommand::run()
{
	ClientHandler &a = ClientHandler::get();

	a.send(cmds);
	std::vector<std::string> res = std::move(a.receive());
	//for (auto& s : res) {
	//	std::cout << s << " " << std::endl;
	//}
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
