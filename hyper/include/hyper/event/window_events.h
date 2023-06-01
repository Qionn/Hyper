#ifndef __HYPER_WINDOW_EVENTS_H__
#define __HYPER_WINDOW_EVENTS_H__

#include "hyper/core/window.h"
#include "hyper/event/event.h"

namespace hyper
{
	class WindowCloseEvent final : public AEvent
	{
	public:
		Window::id_t id;

		WindowCloseEvent(Window::id_t id)
			: id{ id } {}
	};
}

#endif // !__HYPER_WINDOW_EVENTS_H__
