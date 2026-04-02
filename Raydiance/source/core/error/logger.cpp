#include "./pch.h"
#include "./core/error/logger.h"

namespace Raydiance
{

	Logger* Logger::Create(const std::string& _filename)
	{
		return new Logger();
	}

	Logger::Logger()
	{ }

	Logger::~Logger()
	{ }

	void Logger::Log(const std::string& _message, LogLevel _level)
	{
		switch (_level)
		{
		case LogLevel::LOG_LEVEL_INFO:
			printf("[INFO] %s\n", _message.c_str());
			break;
		case LogLevel::LOG_LEVEL_WARNING:
			printf("[WARNING] %s\n", _message.c_str());
			break;
		case LogLevel::LOG_LEVEL_ERROR:
			printf("[ERROR] %s\n", _message.c_str());
			break;
		case LogLevel::LOG_LEVEL_CRITICAL:
			printf("[Critical] %s\n", _message.c_str());
			break;
		}
	}
}