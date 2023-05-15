#ifndef __HYPER_LOGGING_H__
#define __HYPER_LOGGING_H__

#include "hyper/service/service_hub.h"

#include <format>

namespace hyper
{
	template<class ... Args>
	void log(ELogLevel level, std::format_string<Args...> fmt, Args&&... args)
	{
		std::string message = std::format(fmt, std::forward<Args>(args)...);
		ServiceHub::log_service()->log(level, std::move(message));
	}

	template<class ... Args>
	void log_trace(std::format_string<Args...> fmt, Args&&... args)
	{
		log(ELogLevel::eTrace, fmt, std::forward<Args>(args)...);
	}

	template<class ... Args>
	void log_info(std::format_string<Args...> fmt, Args&&... args)
	{
		log(ELogLevel::eInfo, fmt, std::forward<Args>(args)...);
	}

	template<class ... Args>
	void log_warn(std::format_string<Args...> fmt, Args&&... args)
	{
		log(ELogLevel::eWarn, fmt, std::forward<Args>(args)...);
	}

	template<class ... Args>
	void log_error(std::format_string<Args...> fmt, Args&&... args)
	{
		log(ELogLevel::eError, fmt, std::forward<Args>(args)...);
	}

	template<class ... Args>
	void log_fatal(std::format_string<Args...> fmt, Args&&... args)
	{
		log(ELogLevel::eFatal, fmt, std::forward<Args>(args)...);
	}

	template<class ... Args>
	void log_debug(std::format_string<Args...> fmt, Args&&... args)
	{
		log(ELogLevel::eDebug, fmt, std::forward<Args>(args)...);
	}
}

#endif // !__HYPER_LOGGING_H__
