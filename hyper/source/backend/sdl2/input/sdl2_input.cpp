#include "sdl2_input.h"

#include "hyper/event/window_events.h"
#include "hyper/utils/assert.h"

#include <SDL.h>

namespace hyper
{
	Input::Impl::Impl()
	{
		m_pKeyboard		= std::make_unique<Keyboard>();
		m_pDefaultLayer	= std::make_unique<CommandLayer>();

		for (int i = 0; i < SDL_NumJoysticks(); ++i)
		{
			m_Gamepads.push_back(std::make_unique<Gamepad>(i));
		}

		PushLayer(m_pDefaultLayer.get());
	}

	void Input::Impl::Update()
	{
		if (m_pDefaultLayerBuffer != nullptr)
		{
			m_pDefaultLayerBuffer.reset();
		}

		HandleEvents();

		CommandLayer* layer = m_LayerStack.top();
		layer->Update(m_pKeyboard.get());

		for (int i = 0; i < static_cast<int>(m_Gamepads.size()); ++i)
		{
			layer->Update(m_Gamepads[i].get(), i);
		}
	}

	void Input::Impl::PushLayer(CommandLayer* pLayer)
	{
		m_LayerStack.push(pLayer);
	}

	void Input::Impl::Poplayer()
	{
		if (m_LayerStack.size() > 1)
		{
			m_LayerStack.pop();
		}
	}

	void Input::Impl::Bind(Key key, KeyState state, std::unique_ptr<ICommand> command)
	{
		m_LayerStack.top()->Bind(key, state, std::move(command));
	}

	void Input::Impl::Bind(Button button, ButtonState state, int gamepad, std::unique_ptr<ICommand> command)
	{
		m_LayerStack.top()->Bind(button, state, gamepad, std::move(command));
	}

	void Input::Impl::Unbind(Key key, KeyState state)
	{
		m_LayerStack.top()->Unbind(key, state);
	}

	void Input::Impl::Unbind(Button button, ButtonState state, int gamepad)
	{
		m_LayerStack.top()->Unbind(button, state, gamepad);
	}

	void Input::Impl::UnbindAll()
	{
		m_LayerStack.top()->UnbindAll();
	}

	void Input::Impl::Reset()
	{
		while (!m_LayerStack.empty())
		{
			m_LayerStack.pop();
		}

		m_pDefaultLayerBuffer = std::move(m_pDefaultLayer);
		m_pDefaultLayer = std::make_unique<CommandLayer>();
		PushLayer(m_pDefaultLayer.get());
	}

	Keyboard& Input::Impl::GetKeyboard() const
	{
		return *m_pKeyboard;
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

	void Input::Impl::FireEvent(const AEvent& event) const
	{
		HyperAssert(m_Callback != nullptr, "Expected a valid callback");
		m_Callback(event);
	}

	int Input::Impl::GetGamepadCount() const
	{
		return static_cast<int>(m_Gamepads.size());
	}

	Gamepad* Input::Impl::GetGamepad(int index) const
	{
		if (index < static_cast<int>(m_Gamepads.size()))
		{
			return m_Gamepads[index].get();
		}
		return nullptr;
	}
}
