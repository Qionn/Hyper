#include "hyper/input/input.h"

#if defined(HYPER_BACKEND_SDL2)
#	include "backend/sdl2/input/sdl2_input.h"
#endif

namespace hyper
{
	Input::Input()
	{
		m_pImpl = new Impl();
		m_pImpl->SetEventCallback(std::bind(&Input::NotifyObservers, this, std::placeholders::_1));
	}

	Input::~Input()
	{
		delete m_pImpl;
	}

	void Input::PushLayer(CommandLayer* pLayer)
	{
		m_pImpl->PushLayer(pLayer);
	}

	void Input::PopLayer()
	{
		m_pImpl->Poplayer();
	}

	void Input::Update()
	{
		m_pImpl->Update();
	}

	void Input::Bind(Key key, KeyState state, std::unique_ptr<ICommand> command)
	{
		m_pImpl->Bind(key, state, std::move(command));
	}

	void Input::Bind(Button button, ButtonState state, int gamepad, std::unique_ptr<ICommand> command)
	{
		m_pImpl->Bind(button, state, gamepad, std::move(command));
	}

	void Input::Unbind(Key key, KeyState state)
	{
		m_pImpl->Unbind(key, state);
	}

	void Input::Unbind(Button button, ButtonState state, int gamepad)
	{
		m_pImpl->Unbind(button, state, gamepad);
	}

	void Input::UnbindAll()
	{
		m_pImpl->UnbindAll();
	}

	void Input::Reset()
	{
		m_pImpl->Reset();
	}

	int Input::GetGamepadCount() const
	{
		return m_pImpl->GetGamepadCount();
	}

	Keyboard& Input::GetKeyboard() const
	{
		return m_pImpl->GetKeyboard();
	}

	Gamepad* Input::GetGamepad(int index) const
	{
		return m_pImpl->GetGamepad(index);
	}
}
