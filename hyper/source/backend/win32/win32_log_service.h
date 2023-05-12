#ifndef __HYPER_WIN32_LOG_SERVICE_H__
#define __HYPER_WIN32_LOG_SERVICE_H__

#include <string>
#include <atomic>

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include "hyper/service/log_service.h"

namespace hyper
{
	class ConsoleLogService::Impl final
	{
	public:
		Impl(std::string_view name);

		void log(ELogLevel level, std::string_view message);

		Impl(const Impl&)				= delete;
		Impl(Impl&&)					= delete;
		Impl& operator=(const Impl&)	= delete;
		Impl& operator=(Impl&&)			= delete;

		~Impl() = default;

	private:
		std::string m_Name;
		std::atomic_flag m_IsLogging = ATOMIC_FLAG_INIT;

		HANDLE m_Console;
		WORD m_OldAttributes;

	private:
		void begin_color(ELogLevel level);
		void end_color();
	};
}

#endif // !__HYPER_WIN32_LOG_SERVICE_H__
