#include "pch.h"
#include "Logger.h"

#include <spdlog/spdlog.h>

namespace winrt::Audio_Player::Framework
{
	void Logger::OPEN_CONSOLE()
	{
		AllocConsole();
		FILE* stream;
		freopen_s(&stream, "CONOUT$", "w", stdout);
		freopen_s(&stream, "CONOUT$", "w", stderr);
		freopen_s(&stream, "CONIN$", "r", stdin);
	}

	void Audio_Player::Framework::Logger::LOG_EXCEPTION(std::string message)
	{
		spdlog::critical(message);
	}

	void Logger::LOG_INFORMATION(std::string message)
	{
		spdlog::info(message);
	}

	void Logger::LogInfo(std::string const& message)
	{
		spdlog::info(message);
	}

	void Logger::Info(std::wstring const& message)
	{
		LogInfo(winrt::to_string(message));
	}

	void Logger::LogError(std::string const& message)
	{
		spdlog::error(message);
	}

	void Logger::Error(std::wstring const& message)
	{
		LogError(winrt::to_string(message));
	}

	void Logger::LogCritical(std::string const& message)
	{
		spdlog::critical(message);
	}

	void Logger::Critical(std::wstring const& message)
	{
		LogCritical(winrt::to_string(message));
	}

	void Logger::LogTrace(std::string const& message)
	{
		spdlog::trace(message);
	}

	void Logger::Trace(std::wstring const& message)
	{
		LogTrace(winrt::to_string(message));
	}
}