#if defined(HYPER_BACKEND_SDL2)
#	include "backend/sdl2/input/sdl2_gamepad.h"
#endif

namespace hyper
{
	Gamepad::Gamepad(int index)
	{
		m_pImpl = new Impl(index);
	}

	Gamepad::~Gamepad()
	{
		delete m_pImpl;
	}

	void Gamepad::Update()
	{
		m_pImpl->Update();
	}

	bool Gamepad::IsDown(Button button) const
	{
		return m_pImpl->IsDown(button);
	}

	bool Gamepad::IsPressed(Button button) const
	{
		return m_pImpl->IsPressed(button);
	}

	bool Gamepad::IsReleased(Button button) const
	{
		return m_pImpl->IsReleased(button);
	}
}
