#include "pch.h"

#include "hyper/service/service_hub.h"

namespace hyper
{
	/* static */ std::unique_ptr<ILogService> ServiceHub::s_pLogService			= nullptr;
	/* static */ std::unique_ptr<NullLogService> ServiceHub::s_pNullLogService	= std::make_unique<NullLogService>();
	/* static */ ILogService* ServiceHub::s_pActiveLogService					= ServiceHub::s_pNullLogService.get();
}
