#include "sdl2_input.h"

#include "hyper/event/window_events.h"
#include "hyper/utils/assert.h"

#include <SDL.h>

namespace hyper
{
	Input::Impl::Impl()
	{
		m_pKeyboard = std::make_unique<Keyboard>();
	}

	void Input::Impl::Update()
	{
		HandleEvents();
		HandleKeyboardCommands();
	}

	void Input::Impl::Bind(Key key, KeyState state, std::unique_ptr<ICommand> command)
	{
		std::pair<Key, KeyState> keyStatePair(key, state);
		m_KeyboardCommands[keyStatePair] = std::move(command);
	}

	void Input::Impl::Unbind(Key key, KeyState state)
	{
		std::pair<Key, KeyState> keyStatePair(key, state);

		auto it = m_KeyboardCommands.find(keyStatePair);
		if (it != m_KeyboardCommands.end())
		{
			m_KeyboardCommands.erase(it);
		}
	}

	void Input::Impl::ClearBindings()
	{
		m_KeyboardCommands.clear();
	}

	void Input::Impl::SetEventCallback(const EventCallback& callback)
	{
		m_Callback = callback;
	}

	void Input::Impl::HandleEvents()
	{
		SDL_Event sdlEvent;
		while (SDL_PollEvent(&sdlEvent))
		{
			switch (sdlEvent.type)
			{
				case SDL_WINDOWEVENT:
				{
					SDL_Window* pNativeWindow = SDL_GetWindowFromID(sdlEvent.window.windowID);
					auto id = reinterpret_cast<Window::id_t>(SDL_GetWindowData(pNativeWindow, "id"));

					switch (sdlEvent.window.event)
					{
						case SDL_WINDOWEVENT_CLOSE:
						{
							WindowCloseEvent e(id);
							FireEvent(e);
						}
					}
				}
			}
		}
	}

	void Input::Impl::HandleKeyboardCommands()
	{
		m_pKeyboard->Update();

		for (auto& [id, pCommand] : m_KeyboardCommands)
		{
			auto [key, state] = id;

			switch (state)
			{
				case KeyState::eDown:
					if (m_pKeyboard->IsDown(key))
					{
						pCommand->Execute();
					}
					break;

				case KeyState::ePressed:
					if (m_pKeyboard->IsPressed(key))
					{
						pCommand->Execute();
					}
					break;

				case KeyState::eReleased:
					if (m_pKeyboard->IsReleased(key))
					{
						pCommand->Execute();
					}
					break;
			}
		}
	}

	void Input::Impl::FireEvent(const AEvent& event) const
	{
		HyperAssert(m_Callback != nullptr, "Expected a valid callback");
		m_Callback(event);
	}
}
