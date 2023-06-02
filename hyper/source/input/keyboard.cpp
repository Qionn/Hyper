#if defined(HYPER_BACKEND_SDL2)
#	include "backend/sdl2/input/sdl2_keyboard.h"
#endif

namespace hyper
{
	Keyboard::Keyboard()
	{
		m_pImpl = new Impl();
	}

	Keyboard::~Keyboard()
	{
		delete m_pImpl;
	}

	void Keyboard::Update()
	{
		m_pImpl->Update();
	}

	bool Keyboard::IsDown(Key key) const
	{
		return m_pImpl->IsDown(key);
	}

	bool Keyboard::IsPressed(Key key) const
	{
		return m_pImpl->IsPressed(key);
	}

	bool Keyboard::IsReleased(Key key) const
	{
		return m_pImpl->IsReleased(key);
	}
}
