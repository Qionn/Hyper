#ifndef __HYPER_SDL2_INPUT_H__
#define __HYPER_SDL2_INPUT_H__

#include <functional>
#include <map>

#include "hyper/input/input.h"
#include "hyper/input/keyboard.h"

namespace hyper
{
	class Input::Impl final
	{
	public:
		using EventCallback = std::function<void(const AEvent&)>;

	public:
		Impl();

		void Update();

		void Bind(Key key, KeyState state, std::unique_ptr<ICommand> command);
		void Unbind(Key key, KeyState state);

		void ClearBindings();

		void SetEventCallback(const EventCallback& callback);

		Impl(const Impl&)				= delete;
		Impl(Impl&&)					= delete;
		Impl& operator=(const Impl&)	= delete;
		Impl& operator=(Impl&&)			= delete;

		~Impl() = default;

	private:
		std::unique_ptr<Keyboard> m_pKeyboard;
		std::map<std::pair<Key, KeyState>, std::unique_ptr<ICommand>> m_KeyboardCommands;
		EventCallback m_Callback;

	private:
		void HandleEvents();
		void HandleKeyboardCommands();
		void FireEvent(const AEvent& event) const;
	};
}

#endif // !__HYPER_SDL2_INPUT_H__
