#pragma once
#include "./core/error/log_level.h"

#include <string>
#include <string_view>

namespace Raydiance
{
	class Logger
	{
	public:
		static Logger* Create(const std::string& _filename);
		virtual ~Logger();

		static void Log(const std::string& _message, LogLevel _level);

	protected:
		Logger();
	};
}