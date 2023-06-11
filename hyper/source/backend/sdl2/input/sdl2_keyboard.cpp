#include "sdl2_key.h"
#include "sdl2_keyboard.h"

#include <cstring>
#include <algorithm>

namespace hyper
{
	Keyboard::Impl::Impl()
	{
		std::memset(m_CurrentState, 0, sizeof(KeyArray));
		std::memset(m_PrevState, 0, sizeof(KeyArray));
		std::memset(m_Pressed, 0, sizeof(KeyArray));
		std::memset(m_Released, 0, sizeof(KeyArray));
	}

	void Keyboard::Impl::Update()
	{
		int numKeys;
		const Uint8* pCurrentState = SDL_GetKeyboardState(&numKeys);

		std::swap(m_CurrentState, m_PrevState);
		std::copy(pCurrentState, pCurrentState + numKeys, m_CurrentState);

		for (int i = 0; i < numKeys; ++i)
		{
			Uint8 changes = m_CurrentState[i] ^ m_PrevState[i];
			m_Pressed[i] = changes & m_CurrentState[i];
			m_Released[i] = changes & (~m_CurrentState[i]);
		}
	}

	bool Keyboard::Impl::IsDown(Key key) const
	{
		return CheckKeyState(key, m_CurrentState);
	}

	bool Keyboard::Impl::IsPressed(Key key) const
	{
		return CheckKeyState(key, m_Pressed);
	}

	bool Keyboard::Impl::IsReleased(Key key) const
	{
		return CheckKeyState(key, m_Released);
	}

	bool Keyboard::Impl::IsAzerty() const
	{
		bool a = SDL_GetScancodeFromKey(SDLK_a) == SDL_SCANCODE_Q;
		bool z = SDL_GetScancodeFromKey(SDLK_z) == SDL_SCANCODE_W;

		return a && z;
	}

	bool Keyboard::Impl::IsQwerty() const
	{
		bool q = SDL_GetScancodeFromKey(SDLK_q) == SDL_SCANCODE_Q;
		bool w = SDL_GetScancodeFromKey(SDLK_w) == SDL_SCANCODE_W;

		return q && w;
	}

	/* static */ bool Keyboard::Impl::CheckKeyState(Key key, ConstKeyArray keyArray)
	{
		SDL_KeyCode keyCode = KeyToSDL2Key(key);
		SDL_Scancode scancode = SDL_GetScancodeFromKey(keyCode);

		return keyArray[scancode];
	}
}
