#ifndef __HYPER_LOG_SERVICE_H__
#define __HYPER_LOG_SERVICE_H__

#include <string_view>

namespace hyper
{
	enum class ELogLevel
	{
		eTrace,
		eInfo,
		eWarn,
		eError,
		eFatal,
		eDebug
	};

	class ILogService
	{
	public:
		virtual void Log(ELogLevel level, std::string_view message) const = 0;
		virtual ~ILogService() = default;
	};

	class NullLogService final : public ILogService
	{
	public:
		void Log(ELogLevel, std::string_view) const override {};
	};

	class ConsoleLogService final : public ILogService
	{
	public:
		explicit ConsoleLogService(std::string_view name);

		void Log(ELogLevel level, std::string_view message) const override;

		ConsoleLogService(const ConsoleLogService&)				= delete;
		ConsoleLogService(ConsoleLogService&)					= delete;
		ConsoleLogService& operator=(const ConsoleLogService&)	= delete;
		ConsoleLogService& operator=(ConsoleLogService&&)		= delete;

		~ConsoleLogService();

	private:
		class Impl;
		Impl* m_pImpl;
	};
}

#endif // !__HYPER_LOG_SERVICE_H__
