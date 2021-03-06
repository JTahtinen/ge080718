#include "log.h"
#include <iostream>

Log::Log()
{
	_messages.reserve(50);
	_errors.reserve(50);
}

void Log::message(const std::string& message)
{
	_messages.emplace_back(message);
}

void Log::error(const std::string& error)
{
	_errors.emplace_back(error);
}

void Log::logAndPrintMessage(const std::string& message)
{
	Log::message(message);
	printLastMessage();
}

void Log::logAndPrintError(const std::string& error)
{
	Log::error(error);
	printLastError();
}

void Log::printMessages() const
{
	for (const std::string& message : _messages)
	{
		Log::msg(message);
	}
}

void Log::printErrors() const
{
	for (const std::string& error : _errors)
	{
		Log::err(error);
	}
}

void Log::printLastMessage() const
{
	if (!_messages.empty())
	{
		Log::msg(_messages.back());
	}
}

void Log::printLastError() const
{
	if (!_errors.empty())
	{
		Log::err(_errors.back());
	}
}


void Log::msg(const std::string& message)
{
	std::cout << message << std::endl;
}

void Log::err(const std::string& error)
{
	std::cout << "[ERROR] " << error << std::endl;
}

void Log::warning(const std::string& warning)
{
	std::cout << "[WARNING] " << warning << std::endl;
}