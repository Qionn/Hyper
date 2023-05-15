#ifndef __HYPER_WIN32_LOG_SERVICE_H__
#define __HYPER_WIN32_LOG_SERVICE_H__

#include <atomic>
#include <condition_variable>
#include <thread>
#include <queue>

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

		~Impl();

	private:
		struct MessageInfo
		{
			std::string message;
			ELogLevel level;
		};

		std::string m_Name;
		std::jthread m_Thread;
		std::mutex m_Mutex;
		std::condition_variable m_Conditional;
		std::queue<MessageInfo> m_Messages;
		std::atomic_bool m_JoinThread = false;

		HANDLE m_Console;
		WORD m_OldAttributes;

	private:
		void begin_color(ELogLevel level);
		void end_color();

		void thread_function();
	};
}

#endif // !__HYPER_WIN32_LOG_SERVICE_H__
