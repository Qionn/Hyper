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

	void Input::Unbind(Key key, KeyState state)
	{
		m_pImpl->Unbind(key, state);
	}

	void Input::UnbindAll()
	{
		m_pImpl->UnbindAll();
	}

	void Input::Reset()
	{
		m_pImpl->Reset();
	}

	Keyboard& Input::GetKeyboard() const
	{
		return m_pImpl->GetKeyboard();
	}
}
