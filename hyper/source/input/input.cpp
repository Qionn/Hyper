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

	/* static */ Input& Input::Get()
	{
		static Input instance;
		return instance;
	}

	void Input::Update()
	{
		m_pImpl->Update();
	}
}
