#pragma once
#include <string>
#include <vector>

class Log
{
	std::vector<std::string>	_messages;
	std::vector<std::string>	_errors;
public:
	void message(const std::string& message);
	void error(const std::string& error);
	void logAndPrintMessage(const std::string& message);
	void logAndPrintError(const std::string& error);
	void printMessages() const;
	void printErrors() const;
	void printLastMessage() const;
	void printLastError() const;

	static Log& instance()
	{
		static Log log;
		return log;
	}

	static void msg(const std::string& message);
	static void err(const std::string& err);
	static void warning(const std::string& warning);

private:
	Log();
};