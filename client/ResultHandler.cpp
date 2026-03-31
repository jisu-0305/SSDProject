#include "ResultHandler.h"

ResultHandler& ResultHandler::get()
{
	static ResultHandler handler;
	return handler;
}
void ResultHandler::setResult(std::string order, std::string res) {
	this->order = order;
	this->result = res;
}
std::pair<std::string, std::string> ResultHandler::getResult() {
	return { order, result };
}