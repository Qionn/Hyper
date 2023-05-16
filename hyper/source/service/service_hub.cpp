#include "hyper/service/service_hub.h"

namespace hyper
{
	/* static */ std::unique_ptr<ILogService> ServiceHub::s_pLogService		= std::make_unique<NullLogService>();
	/* static */ std::unique_ptr<ISoundService> ServiceHub::s_pSoundService	= std::make_unique<NullSoundService>();
}
