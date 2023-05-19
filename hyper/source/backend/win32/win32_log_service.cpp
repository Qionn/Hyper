#include "win32_log_service.h"

#include <cstdio>
#include <ctime>

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

	void ConsoleLogService::Impl::Log(ELogLevel level, std::string_view message)
	{
		std::time_t currentTime = std::time(nullptr);
		std::tm localTime;
		localtime_s(&localTime, &currentTime);

		char timeBuffer[9];
		std::strftime(timeBuffer, ARRAYSIZE(timeBuffer), "%H:%M:%S", &localTime);

		BeginColor(level);
		std::fprintf(stdout, "[%s] <%s> %s\n", timeBuffer, m_Name.c_str(), message.data());
		EndColor();
	}

	void ConsoleLogService::Impl::BeginColor(ELogLevel level)
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

	void ConsoleLogService::Impl::EndColor()
	{
		SetConsoleTextAttribute(m_Console, m_OldAttributes);
	}
}
