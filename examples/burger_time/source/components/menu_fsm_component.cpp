#include "menu_fsm_component.h"

#include <hyper/service/service_hub.h>

using namespace hyper;

namespace burger_time
{
	MenuFSMComponent::MenuFSMComponent(Actor& actor)
		: AComponent(actor)
	{
		ISoundService* pSoundService = ServiceHub::SoundService();
		m_SoundId = pSoundService->AddSound("assets/audio/menu_navigate_02.wav");

		m_pDefaultState = std::make_unique<MainMenuState>(this);
		
		m_Stack.push(m_pDefaultState.get());
		m_Stack.top()->OnEnter();
	}

	void MenuFSMComponent::PushMenuState(AMenuState* pState)
	{
		ISoundService* pSoundService = ServiceHub::SoundService();
		pSoundService->Play(m_SoundId, 0.5f);

		if (!m_Stack.empty())
		{
			m_Stack.top()->OnExit();
		}

		m_Stack.push(pState);
		pState->OnEnter();
	}

	void MenuFSMComponent::PopMenuState()
	{
		if (m_Stack.size() > 1)
		{
			ISoundService* pSoundService = ServiceHub::SoundService();
			pSoundService->Play(m_SoundId, 0.5f);

			m_Stack.top()->OnExit();
			m_Stack.pop();
			m_Stack.top()->OnEnter();
		}
	}

	AMenuState* MenuFSMComponent::GetCurrentMenuState() const
	{
		return m_Stack.top();
	}

	void MenuFSMComponent::OnUpdate(float)
	{

	}

	void MenuFSMComponent::OnRender(const IContext&) const
	{

	}
}
