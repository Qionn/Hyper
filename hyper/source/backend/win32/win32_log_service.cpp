#include "pch.h"

#include "win32_log_service.h"

#include <cstdio>
#include <ctime>
#include <thread>

namespace hyper
{
	ConsoleLogService::Impl::Impl(std::string_view name)
		: m_Name{ name }
	{
		m_Console = GetStdHandle(STD_OUTPUT_HANDLE);

		CONSOLE_SCREEN_BUFFER_INFO screenInfo;
		GetConsoleScreenBufferInfo(m_Console, &screenInfo);
		m_OldAttributes = screenInfo.wAttributes;
	}

	void ConsoleLogService::Impl::log(ELogLevel level, std::string_view message)
	{
		std::time_t currentTime = std::time(nullptr);
		std::tm localTime;
		localtime_s(&localTime, &currentTime);

		char timeBuffer[9];
		std::strftime(timeBuffer, sizeof(timeBuffer), "%H:%M:%S", &localTime);

		while (m_IsLogging.test_and_set(std::memory_order_acquire))
		{
			std::this_thread::yield();
		}

		begin_color(level);
		std::fprintf(stdout, "[%s] <%s> %s\n", timeBuffer, m_Name.c_str(), message.data());
		end_color();

		m_IsLogging.clear(std::memory_order_release);
	}

	void ConsoleLogService::Impl::begin_color(ELogLevel level)
	{
		WORD attribs = m_OldAttributes;

		switch (level)
		{
			case ELogLevel::eTrace:
				attribs = FOREGROUND_INTENSITY;
				break;

			case ELogLevel::eInfo:
				attribs = FOREGROUND_GREEN;
				break;

			case ELogLevel::eWarn:
				attribs = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY;
				break;

			case ELogLevel::eError:
				attribs = FOREGROUND_RED | FOREGROUND_INTENSITY;
				break;

			case ELogLevel::eFatal:
				attribs = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE |
					FOREGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_INTENSITY;
				break;

			case ELogLevel::eDebug:
				attribs = FOREGROUND_RED | FOREGROUND_BLUE;
				break;
		}

		SetConsoleTextAttribute(m_Console, attribs);
	}

	void ConsoleLogService::Impl::end_color()
	{
		SetConsoleTextAttribute(m_Console, m_OldAttributes);
	}
}
