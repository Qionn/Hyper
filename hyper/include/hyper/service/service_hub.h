#ifndef __HYPER_SERVICE_HUB_H__
#define __HYPER_SERVICE_HUB_H__

#include <concepts>
#include <memory>
#include <utility>

#include "hyper/service/log_service.h"
#include "hyper/service/sound_service.h"

namespace hyper
{
	class ServiceHub final
	{
	public:
		static ILogService* LogService() { return s_pLogService.get(); }
		static ISoundService* SoundService() { return s_pSoundService.get(); }

		template<class T, class ... Args> requires std::derived_from<T, ILogService>
		static void RegisterService(Args&&... args)
		{
			s_pLogService = std::make_unique<T>(std::forward<Args>(args)...);
		}

		template<class T, class ... Args> requires std::derived_from<T, ISoundService>
		static void RegisterService(Args&&... args)
		{
			s_pSoundService = std::make_unique<T>(std::forward<Args>(args)...);
		}

	private:
		static std::unique_ptr<ILogService> s_pLogService;
		static std::unique_ptr<ISoundService> s_pSoundService;
	};
}

#endif // !__HYPER_SERVICE_HUB_H__
