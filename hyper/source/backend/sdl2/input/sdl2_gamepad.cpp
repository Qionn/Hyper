#include "sdl2_button.h"
#include "sdl2_gamepad.h"

#include "hyper/utils/assert.h"

namespace hyper
{
	Gamepad::Impl::Impl(int index)
		: m_CurrentState{ 0 }
		, m_PrevState{ 0 }
		, m_Pressed{ 0 }
		, m_Released{ 0 }
	{
		m_pController = SDL_GameControllerOpen(index);
		HyperAssert(m_pController != nullptr, "Failed to open gamepad");
	}

	Gamepad::Impl::~Impl()
	{
		SDL_GameControllerClose(m_pController);
	}

	void Gamepad::Impl::Update()
	{
		m_PrevState = m_CurrentState;
		m_CurrentState = GetCurrentState();

		int changes = m_CurrentState ^ m_PrevState;
		m_Pressed = changes & m_CurrentState;
		m_Released = changes & (~m_CurrentState);
	}

	bool Gamepad::Impl::IsDown(Button button) const
	{
		return CheckButtonState(m_CurrentState, button);
	}

	bool Gamepad::Impl::IsPressed(Button button) const
	{
		return CheckButtonState(m_Pressed, button);
	}

	bool Gamepad::Impl::IsReleased(Button button) const
	{
		return CheckButtonState(m_Released, button);
	}

	int Gamepad::Impl::GetCurrentState() const
	{
		int state = 0;

		for (int i = 0; i < static_cast<int>(Button::eMax); ++i)
		{
			state |= GetButtonState(static_cast<Button>(i));
		}

		return state;
	}

	int Gamepad::Impl::GetButtonState(Button button) const
	{
		SDL_GameControllerButton sdlButton = ButtonToSDL2Button(button);
		auto state = static_cast<int>(SDL_GameControllerGetButton(m_pController, sdlButton));
		state <<= static_cast<int>(button);
		return state;
	}

	/* static */ bool Gamepad::Impl::CheckButtonState(int state, Button button)
	{
		state >>= static_cast<int>(button);
		state &= 0x01;

		return (state == 0x01);
	}
}
