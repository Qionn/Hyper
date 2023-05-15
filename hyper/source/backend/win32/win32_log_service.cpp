#include "pch.h"

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

		m_Thread = std::jthread(&Impl::thread_function, this);
	}

	ConsoleLogService::Impl::~Impl()
	{
		m_JoinThread = true;
		m_Thread.join();
	}

	void ConsoleLogService::Impl::log(ELogLevel level, std::string_view message)
	{
		{
			std::lock_guard lock(m_Mutex);
			m_Messages.push({ std::string(message), level });
		}
		m_Conditional.notify_one();
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

	void ConsoleLogService::Impl::thread_function()
	{
		while (true)
		{
			std::unique_lock lock(m_Mutex);
			m_Conditional.wait(lock, [this]() { return !m_Messages.empty() || m_JoinThread; });

			if (m_JoinThread && m_Messages.empty())
			{
				break;
			}

			MessageInfo info = std::move(m_Messages.front());
			m_Messages.pop();

			lock.unlock();

			std::time_t currentTime = std::time(nullptr);
			std::tm localTime;
			localtime_s(&localTime, &currentTime);

			char timeBuffer[9];
			std::strftime(timeBuffer, ARRAYSIZE(timeBuffer), "%H:%M:%S", &localTime);

			begin_color(info.level);
			std::fprintf(stdout, "[%s] <%s> %s\n", timeBuffer, m_Name.c_str(), info.message.c_str());
			end_color();
		}
	}
}
