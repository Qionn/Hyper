#ifndef __HYPER_SDL2_KEYBOARD_H__
#define __HYPER_SDL2_KEYBOARD_H__

#include <SDL.h>

#include "hyper/input/keyboard.h"

namespace hyper
{
	class Keyboard::Impl final
	{
	public:
		Impl();

		void Update();

		bool IsDown(Key key) const;
		bool IsPressed(Key key) const;
		bool IsReleased(Key key) const;

		Impl(const Impl&)				= delete;
		Impl(Impl&&)					= delete;
		Impl& operator=(const Impl&)	= delete;
		Impl& operator=(Impl&&)			= delete;

		~Impl() = default;

	private:
		using KeyArray = Uint8[SDL_NUM_SCANCODES];
		using ConstKeyArray = const Uint8[SDL_NUM_SCANCODES];

		KeyArray m_CurrentState, m_PrevState;
		KeyArray m_Pressed, m_Released;

	private:
		static bool CheckKeyState(Key key, ConstKeyArray keyArray);
	};
}

#endif // !__HYPER_SDL2_KEYBOARD_H__
