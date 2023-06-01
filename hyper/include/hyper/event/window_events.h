#ifndef __HYPER_WINDOW_EVENTS_H__
#define __HYPER_WINDOW_EVENTS_H__

#include "hyper/event/event.h"
#include "hyper/fwd.h"

namespace hyper
{
	class WindowCloseEvent final : public AEvent
	{
	public:
		const Window* pWindow;

		WindowCloseEvent(const Window* pWindow)
			: pWindow{ pWindow } {}
	};
}

#endif // !__HYPER_WINDOW_EVENTS_H__
