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

		m_Thread = std::jthread(&Impl::ThreadFunction, this);
	}

	ConsoleLogService::Impl::~Impl()
	{
		m_JoinThread = true;
		m_Conditional.notify_all();
		m_Thread.join();
	}

	void ConsoleLogService::Impl::Log(ELogLevel level, std::string_view message)
	{
		{
			std::lock_guard lock(m_Mutex);
			m_Messages.push({ std::string(message), level });
		}
		m_Conditional.notify_one();
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

	void ConsoleLogService::Impl::ThreadFunction()
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

			BeginColor(info.level);
			std::fprintf(stdout, "[%s] <%s> %s\n", timeBuffer, m_Name.c_str(), info.message.c_str());
			EndColor();
		}
	}
}
