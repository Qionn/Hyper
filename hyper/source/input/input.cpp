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

	void Input::Update()
	{
		m_pImpl->Update();
	}

	void Input::Bind(Key key, KeyState state, std::unique_ptr<ICommand> command)
	{
		m_pImpl->Bind(key, state, std::move(command));
	}

	void Input::Unbind(Key key, KeyState state)
	{
		m_pImpl->Unbind(key, state);
	}

	void Input::ClearBindings()
	{
		m_pImpl->ClearBindings();
	}
}
