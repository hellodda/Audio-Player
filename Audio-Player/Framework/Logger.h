#pragma once

#include "ILogger.h"

namespace winrt::Audio_Player::Framework
{
	struct Logger : public ILogger
	{
	public:

		static void OPEN_CONSOLE();
		static void LOG_EXCEPTION(std::string message);
		static void LOG_INFORMATION(std::string message);

		void LogInfo(std::string const& message) override;
		void Info(std::wstring const& message);

		void LogError(std::string const& message) override;
		void Error(std::wstring const& message);

		void LogCritical(std::string const& message) override;
		void Critical(std::wstring const& message);

		void LogTrace(std::string const& message) override;
		void Trace(std::wstring const& message);
	};
}

