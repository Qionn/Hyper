#include "sdl2_input.h"

#include "hyper/event/window_events.h"
#include "hyper/utils/assert.h"

#include <SDL.h>

namespace hyper
{
	void Input::Impl::Update()
	{
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
				case SDL_WINDOWEVENT:
				{
					SDL_Window* pNativeWindow = SDL_GetWindowFromID(event.window.windowID);
					auto pWindow = static_cast<const Window*>(SDL_GetWindowData(pNativeWindow, "hyper_window"));

					switch (event.window.event)
					{
						case SDL_WINDOWEVENT_CLOSE:
						{
							WindowCloseEvent e(pWindow);
							FireEvent(e);
						}
					}
				}
			}
		}
	}

	void Input::Impl::SetEventCallback(const EventCallback& callback)
	{
		m_Callback = callback;
	}

	void Input::Impl::FireEvent(const AEvent& event) const
	{
		HyperAssert(m_Callback != nullptr, "Expected a valid callback");
		m_Callback(event);
	}
}
