#pragma once

#include <string>

namespace winrt::Audio_Player::Framework
{
	struct ILogger
	{
	public:

		virtual void LogInfo(std::string const& message) = 0;
		virtual void LogError(std::string const& message) = 0;
		virtual void LogCritical(std::string const& message) = 0;
		virtual void LogTrace(std::string const& message) = 0;
		virtual void LogWarning(std::string const& message) = 0;
	};
}