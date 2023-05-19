#ifndef __HYPER_WIN32_LOG_SERVICE_H__
#define __HYPER_WIN32_LOG_SERVICE_H__

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include "hyper/service/log_service.h"

namespace hyper
{
	class ConsoleLogService::Impl final
	{
	public:
		Impl(std::string_view name);

		void Log(ELogLevel level, std::string_view message);

		Impl(const Impl&)				= delete;
		Impl(Impl&&)					= delete;
		Impl& operator=(const Impl&)	= delete;
		Impl& operator=(Impl&&)			= delete;

		~Impl() = default;

	private:
		std::string m_Name;

		HANDLE m_Console;
		WORD m_OldAttributes;

	private:
		void BeginColor(ELogLevel level);
		void EndColor();
	};
}

#endif // !__HYPER_WIN32_LOG_SERVICE_H__
