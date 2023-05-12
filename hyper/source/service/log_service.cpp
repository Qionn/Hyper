#include "pch.h"

#if defined(HYPER_BACKEND_WIN32)
#	include "backend/win32/win32_log_service.h"
#endif

namespace hyper
{
	ConsoleLogService::ConsoleLogService(std::string_view name)
	{
		m_pImpl = new Impl(name);
	}

	void ConsoleLogService::log(ELogLevel level, std::string_view message) const
	{
		m_pImpl->log(level, message);
	}

	ConsoleLogService::~ConsoleLogService()
	{
		delete m_pImpl;
	}
}
