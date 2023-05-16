#ifndef __HYPER_LOGGING_H__
#define __HYPER_LOGGING_H__

#include "hyper/service/service_hub.h"

#include <format>

namespace hyper
{
	template<class ... Args>
	void Log(ELogLevel level, std::format_string<Args...> fmt, Args&&... args)
	{
		std::string message = std::format(fmt, std::forward<Args>(args)...);
		ServiceHub::LogService()->Log(level, std::move(message));
	}

	template<class ... Args>
	void LogTrace(std::format_string<Args...> fmt, Args&&... args)
	{
		Log(ELogLevel::eTrace, fmt, std::forward<Args>(args)...);
	}

	template<class ... Args>
	void LogInfo(std::format_string<Args...> fmt, Args&&... args)
	{
		Log(ELogLevel::eInfo, fmt, std::forward<Args>(args)...);
	}

	template<class ... Args>
	void LogWarn(std::format_string<Args...> fmt, Args&&... args)
	{
		Log(ELogLevel::eWarn, fmt, std::forward<Args>(args)...);
	}

	template<class ... Args>
	void LogError(std::format_string<Args...> fmt, Args&&... args)
	{
		Log(ELogLevel::eError, fmt, std::forward<Args>(args)...);
	}

	template<class ... Args>
	void LogFatal(std::format_string<Args...> fmt, Args&&... args)
	{
		Log(ELogLevel::eFatal, fmt, std::forward<Args>(args)...);
	}

	template<class ... Args>
	void LogDebug(std::format_string<Args...> fmt, Args&&... args)
	{
		Log(ELogLevel::eDebug, fmt, std::forward<Args>(args)...);
	}
}

#endif // !__HYPER_LOGGING_H__
