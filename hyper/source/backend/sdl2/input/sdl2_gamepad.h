#ifndef __HYPER_SDL2_GAMEPAD_H__
#define __HYPER_SDL2_GAMEPAD_H__

#include <SDL.h>

#include "hyper/input/gamepad.h"

namespace hyper
{
	class Gamepad::Impl final
	{
	public:
		Impl(int index);

		void Update();

		bool IsDown(Button button) const;
		bool IsPressed(Button button) const;
		bool IsReleased(Button button) const;

		Impl(const Impl&) = delete;
		Impl(Impl&&) = delete;
		Impl& operator=(const Impl&) = delete;
		Impl& operator=(Impl&&) = delete;

		~Impl();

	private:
		SDL_GameController* m_pController;

		int m_CurrentState, m_PrevState;
		int m_Pressed, m_Released;

	private:
		int GetCurrentState() const;
		int GetButtonState(Button button) const;

		static bool CheckButtonState(int state, Button button);
	};
}

#endif // !__HYPER_SDL2_GAMEPAD_H__
