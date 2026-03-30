#pragma once
#include <string>
class Errcodes
{
private:
	int no;
	std::string lore;
	Errcodes() {};
public:
	static Errcodes& get();
	std::string& getErrorMsg();
	void makeError(int errn);
};

