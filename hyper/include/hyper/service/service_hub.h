#ifndef __HYPER_SERVICE_HUB_H__
#define __HYPER_SERVICE_HUB_H__

#include <concepts>
#include <memory>
#include <utility>

#include "hyper/service/log_service.h"

namespace hyper
{
	class ServiceHub final
	{
	public:
		static ILogService* log_service() { return s_pActiveLogService; }

		template<class T, class ... Args> requires std::derived_from<T, ILogService>
		static void register_service(Args&&... args)
		{
			s_pLogService = std::make_unique<T>(std::forward<Args>(args)...);
			s_pActiveLogService = s_pLogService.get();
		}

	private:
		static std::unique_ptr<ILogService> s_pLogService;
		static std::unique_ptr<NullLogService> s_pNullLogService;
		static ILogService* s_pActiveLogService;
	};
}

#endif // !__HYPER_SERVICE_HUB_H__
